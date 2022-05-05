// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_instance.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_surface.h"
#include "vulkan_utils.h"

#if defined(CHR_PLATFORM_WINDOWS)
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#elif defined(CHR_PLATFORM_MACOS)
#include <vulkan/vulkan_macos.h>
#endif

namespace chr::renderer::internal {

static VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
              [[maybe_unused]] void *pUserData) {
  if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    log::Debug("{}", pCallbackData->pMessage);
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    log::Info("{}", pCallbackData->pMessage);
  } else if (messageSeverity &
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    log::Warn("{}", pCallbackData->pMessage);
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    log::Err("{}", pCallbackData->pMessage);
  }

  return VK_FALSE;
}

static VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

static void DestroyDebugUtilsMessengerEXT(
    VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

VulkanInstance::VulkanInstance(const InstanceCreateInfo &info) {
  CHR_ZONE_SCOPED_VULKAN();

  log::Debug("Vulkan init");

  // prepare layers and extesions
  if (info.debug_level != DebugLevel::kNone) {
    required_extensions_.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    required_layers_.push_back("VK_LAYER_KHRONOS_validation");
  }

  if (!info.required_extensions.empty()) {
    for (auto &extension : info.required_extensions) {
      required_extensions_.push_back(extension.c_str());
    }
  } else {
#if defined(CHR_PLATFORM_WINDOWS)
    required_extensions_.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    required_extensions_.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(CHR_PLATFORM_MACOS)
    required_extensions_.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    required_extensions_.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);

    // required from VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME (MolteVK)
    required_extensions_.push_back(
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif
  }

  // get and log vulkan driver version
  uint32_t version{0};
  if (auto result = vkEnumerateInstanceVersion(&version);
      result != VK_SUCCESS) {
    throw VulkanException(result,
                          "Failed to enumerate Vulkan instance version");
  }

  log::Info("Vulkan version: {}.{}.{} (variant {})",
            VK_API_VERSION_MAJOR(version), VK_API_VERSION_MINOR(version),
            VK_API_VERSION_PATCH(version), VK_API_VERSION_VARIANT(version));

  // create application info
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = info.application_name.c_str();
  app_info.applicationVersion = VK_MAKE_VERSION(info.application_version.major,
                                                info.application_version.minor,
                                                info.application_version.patch);
  app_info.pEngineName = info.engine_name.c_str();
  app_info.engineVersion =
      VK_MAKE_VERSION(info.engine_version.major, info.engine_version.minor,
                      info.engine_version.patch);
  app_info.apiVersion = VK_API_VERSION_1_2;

  // validate extensions and layers
  ValidateLayers();
  ValidateExtensions();

  // create initilization parameters
  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount =
      static_cast<uint32_t>(required_extensions_.size());
  create_info.ppEnabledExtensionNames = required_extensions_.data();
  create_info.enabledLayerCount =
      static_cast<uint32_t>(required_layers_.size());
  create_info.ppEnabledLayerNames = required_layers_.data();

  // initialize vulkan
  if (auto result = vkCreateInstance(&create_info, nullptr, &instance_);
      result != VK_SUCCESS) {
    throw VulkanException(result, "Failed to create Vulkan instance");
  }

  try {
    SetupDebugMessenger(info.debug_level);
  } catch (std::exception) {
    vkDestroyInstance(instance_, nullptr);
    throw;
  }

  debug::Assert(instance_ != VK_NULL_HANDLE, "instance_ can't be null");
}

VulkanInstance::~VulkanInstance() {
  CHR_ZONE_SCOPED_VULKAN();

  if (instance_ != VK_NULL_HANDLE) {
    if (debug_messenger_ != VK_NULL_HANDLE) {
      DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
    }
    vkDestroyInstance(instance_, nullptr);
  }
}

auto VulkanInstance::CreateSurface(const SurfaceCreateInfo &info) -> Surface {
  return std::make_shared<VulkanSurface>(*this, info);
}

auto VulkanInstance::CreateDevice(const Surface &surface) -> Device {
  return std::make_shared<VulkanDevice>(
      *this, *static_cast<VulkanSurface *>(surface.get()));
}

auto VulkanInstance::GetLayers() const -> std::vector<VkLayerProperties> {
  CHR_ZONE_SCOPED_VULKAN();

  uint32_t count;
  if (auto result = vkEnumerateInstanceLayerProperties(&count, nullptr);
      result != VK_SUCCESS) {
    throw VulkanException(result,
                          "Failed to enumerate Vulkan layer properties");
  }

  if (count == 0) {
    return {};
  }

  std::vector<VkLayerProperties> layers(count);
  if (auto result = vkEnumerateInstanceLayerProperties(&count, layers.data());
      result != VK_SUCCESS) {
    throw VulkanException(result,
                          "Failed to enumerate Vulkan layer properties");
  }

  return layers;
}

auto VulkanInstance::GetExtensions() const
    -> std::vector<VkExtensionProperties> {
  CHR_ZONE_SCOPED_VULKAN();

  uint32_t count = 0;
  if (auto result =
          vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
      result != VK_SUCCESS) {
    throw VulkanException(result,
                          "Failed to enumerate Vulkan extension properties");
  }

  if (count == 0) {
    return {};
  }

  std::vector<VkExtensionProperties> extensions(count);
  if (auto result = vkEnumerateInstanceExtensionProperties(nullptr, &count,
                                                           extensions.data());
      result != VK_SUCCESS) {
    throw VulkanException(result,
                          "Failed to enumerate Vulkan extension properties");
  }

  return extensions;
}

auto VulkanInstance::SetupDebugMessenger(DebugLevel level) -> void {
  CHR_ZONE_SCOPED_VULKAN();

  if (level == DebugLevel::kNone) {
    return;
  }

  VkDebugUtilsMessageSeverityFlagsEXT severityFlags = 0;
  switch (level) {
    case DebugLevel::kVerbose:
      severityFlags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    case DebugLevel::kWarning:
      severityFlags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
    case DebugLevel::kError:
      severityFlags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
      break;
    default:
      break;
  }

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = severityFlags;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = DebugCallback;
  createInfo.pUserData = nullptr;  // Optional

  if (auto result = CreateDebugUtilsMessengerEXT(instance_, &createInfo,
                                                 nullptr, &debug_messenger_);
      result != VK_SUCCESS) {
    throw VulkanException(result, "Failed to set up debug messenger");
  }
}

auto VulkanInstance::ValidateLayers() const -> void {
  CHR_ZONE_SCOPED_VULKAN();

  log::Debug("Requested layers:");
  for (const auto &layer : required_layers_) {
    log::Debug("  - {}", layer);
  }

  auto available_layers = GetLayers();

  log::Debug("Available layers:");
  for (const auto &available_layer : available_layers) {
    log::Debug("  - {}", available_layer.layerName);
  }

  for (const auto &layer : required_layers_) {
    bool found = false;
    for (const auto &available_layer : available_layers) {
      if (std::strcmp(layer, available_layer.layerName) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      throw RendererException(Error::kLayerNotPresent,
                              fmt::format("Layer {} not found", layer));
    }
  }
}

auto VulkanInstance::ValidateExtensions() const -> void {
  CHR_ZONE_SCOPED_VULKAN();

  log::Debug("Requested extensions:");
  for (const auto &extension : required_extensions_) {
    log::Debug("  - {}", extension);
  }

  auto available_extensions = GetExtensions();

  log::Debug("Available extensions:");
  for (const auto &availableExtension : available_extensions) {
    log::Debug("  - {}", availableExtension.extensionName);
  }

  for (const auto &extension : required_extensions_) {
    bool found = false;
    for (const auto &available_extension : available_extensions) {
      if (std::strcmp(extension, available_extension.extensionName) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      throw RendererException(Error::kExtensionNotPresent,
                              fmt::format("Extension {} not found", extension));
    }
  }
}

}  // namespace chr::renderer::internal