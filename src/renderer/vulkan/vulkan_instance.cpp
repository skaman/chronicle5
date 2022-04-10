#include "pch.h"
#include "vulkan_instance.h"

#if defined(CHR_PLATFORM_WINDOWS)
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#elif defined(CHR_PLATFORM_MACOS)
#include <vulkan/vulkan_macos.h>
#endif

namespace chr::renderer {

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
              [[maybe_unused]] void *pUserData) {
  if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    log::debug("{}", pCallbackData->pMessage);
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    log::info("{}", pCallbackData->pMessage);
  } else if (messageSeverity &
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    log::warn("{}", pCallbackData->pMessage);
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    log::err("{}", pCallbackData->pMessage);
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

static void
DestroyDebugUtilsMessengerEXT(VkInstance instance,
                              VkDebugUtilsMessengerEXT debugMessenger,
                              const VkAllocationCallbacks *pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

VulkanInstance::VulkanInstance(const InstanceInfo &info) {
  log::debug("Vulkan init");

  // prepare layers and extesions
  if (info.debug_level != DebugLevel::none) {
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
  if (vkEnumerateInstanceVersion(&version) != VK_SUCCESS) {
    throw VulkanException("Failed to enumerate Vulkan instance version");
  }

  log::info("Vulkan version: {}.{}.{} (variant {})",
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
  validate_layers();
  validate_extensions();

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
  if (vkCreateInstance(&create_info, nullptr, &instance_) != VK_SUCCESS) {
    throw VulkanException("Failed to create Vulkan instance");
  }

  try {
    setup_debug_messenger(info.debug_level);
  } catch (std::exception) {
    vkDestroyInstance(instance_, nullptr);
    throw;
  }

  debug::assert_true(instance_ != VK_NULL_HANDLE, "instance_ can't be null");
}

VulkanInstance::~VulkanInstance() {
  if (debug_messenger_) {
    DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
  }
  vkDestroyInstance(instance_, nullptr);
}

auto VulkanInstance::test() -> void { chr::log::info("vulkan test"); }

auto VulkanInstance::layers() const -> std::vector<VkLayerProperties> {
  uint32_t count;
  if (vkEnumerateInstanceLayerProperties(&count, nullptr) != VK_SUCCESS) {
    throw VulkanException("Failed to enumerate Vulkan layer properties");
  }

  std::vector<VkLayerProperties> layers(count);
  if (vkEnumerateInstanceLayerProperties(&count, layers.data()) != VK_SUCCESS) {
    throw VulkanException("Failed to enumerate Vulkan layer properties");
  }

  return layers;
}

auto VulkanInstance::extensions() const -> std::vector<VkExtensionProperties> {
  uint32_t count = 0;
  if (vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr) !=
      VK_SUCCESS) {
    throw VulkanException("Failed to enumerate Vulkan extension properties");
  }

  std::vector<VkExtensionProperties> extensions(count);
  if (vkEnumerateInstanceExtensionProperties(nullptr, &count,
                                             extensions.data()) != VK_SUCCESS) {
    throw VulkanException("Failed to enumerate Vulkan extension properties");
  }

  return extensions;
}

auto VulkanInstance::setup_debug_messenger(DebugLevel level) -> void {
  if (level == DebugLevel::none) {
    return;
  }

  VkDebugUtilsMessageSeverityFlagsEXT severityFlags = 0;
  switch (level) {
  case DebugLevel::verbose:
    severityFlags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
  case DebugLevel::warning:
    severityFlags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
  case DebugLevel::error:
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
  createInfo.pfnUserCallback = debugCallback;
  createInfo.pUserData = nullptr; // Optional

  if (CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr,
                                   &debug_messenger_) != VK_SUCCESS) {
    throw VulkanException("Failed to set up debug messenger");
  }
}

auto VulkanInstance::validate_layers() const -> void {
  log::debug("Requested layers:");
  for (const auto &layer : required_layers_) {
    log::debug("  - {}", layer);
  }

  auto available_layers = layers();

  log::debug("Available layers:");
  for (const auto &available_layer : available_layers) {
    log::debug("  - {}", available_layer.layerName);
  }

  for (const auto &layer : required_layers_) {
    bool found = false;
    for (const auto &available_layer : available_layers) {
      if (strcmp(layer, available_layer.layerName) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      throw VulkanException(fmt::format("Layer {} not found", layer));
    }
  }
}

auto VulkanInstance::validate_extensions() const -> void {
  log::debug("Requested extensions:");
  for (const auto &extension : required_extensions_) {
    log::debug("  - {}", extension);
  }

  auto available_extensions = extensions();

  log::debug("Available extensions:");
  for (const auto &availableExtension : available_extensions) {
    log::debug("  - {}", availableExtension.extensionName);
  }

  for (const auto &extension : required_extensions_) {
    bool found = false;
    for (const auto &available_extension : available_extensions) {
      if (strcmp(extension, available_extension.extensionName) == 0) {
        found = true;
        break;
      }
    }

    if (!found) {
      throw VulkanException(fmt::format("Extension {} not found", extension));
    }
  }
}

} // namespace chr::renderer