// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_device.h"

#include "common.h"
#include "vulkan_instance.h"
#include "vulkan_surface.h"

namespace chr::renderer::internal {
VulkanDevice::VulkanDevice(const VulkanInstance &instance,
                           const VulkanSurface &surface)
    : instance_{instance}, surface_{surface} {
  device_extensions_.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

#if defined(CHR_PLATFORM_MACOS)
  // enable support for MoltenVK virtual driver
  device_extensions_.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
#endif

  PickPhysicalDevice();
  CreateLogicalDevice();
}

VulkanDevice::~VulkanDevice() { vkDestroyDevice(device_, nullptr); }

auto VulkanDevice::GetPhysicalDevices() const -> std::vector<VkPhysicalDevice> {
  uint32_t count = 0;
  vkEnumeratePhysicalDevices(instance_.GetNativeInstance(), &count, nullptr);
  if (count == 0) {
    throw RendererException("Failed to find GPUs with Vulkan support");
  }

  std::vector<VkPhysicalDevice> devices(count);
  vkEnumeratePhysicalDevices(instance_.GetNativeInstance(), &count,
                             devices.data());
  return devices;
}

auto VulkanDevice::GetQueueFamilies(VkPhysicalDevice device) const
    -> std::vector<VkQueueFamilyProperties> {
  uint32_t count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

  std::vector<VkQueueFamilyProperties> families(count);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &count, families.data());

  return families;
}

auto VulkanDevice::GetExtensions(VkPhysicalDevice device) const
    -> std::vector<VkExtensionProperties> {
  uint32_t count;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

  std::vector<VkExtensionProperties> extensions(count);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &count,
                                       extensions.data());
  return extensions;
}

auto VulkanDevice::FindQueueFamilies(VkPhysicalDevice device) const
    -> QueueFamilyIndices {
  QueueFamilyIndices indices;

  auto families = GetQueueFamilies(device);

  int i = 0;
  for (const auto &family : families) {
    if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphics_family = i;
    }

    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface_.GetNativeSurface(),
                                         &present_support);
    if (present_support) {
      indices.present_family = i;
    }

    if (indices.IsComplete()) {
      break;
    }

    i++;
  }

  return indices;
}

auto VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice device) const
    -> SwapChainSupportDetails {
  SwapChainSupportDetails details;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface_.GetNativeSurface(),
                                            &details.capabilities);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_.GetNativeSurface(),
                                       &format_count, nullptr);

  if (format_count != 0) {
    details.formats.resize(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_.GetNativeSurface(),
                                         &format_count, details.formats.data());
  }

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface_.GetNativeSurface(),
                                            &present_mode_count, nullptr);
  if (present_mode_count != 0) {
    details.present_modes.resize(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        device, surface_.GetNativeSurface(), &present_mode_count,
        details.present_modes.data());
  }

  return details;
}

auto VulkanDevice::PickPhysicalDevice() -> void {
  auto devices = GetPhysicalDevices();

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, VkPhysicalDevice> candidates;

  for (const auto &device : devices) {
    if (IsDeviceSuitable(device)) {
      int score = RateDeviceSuitability(device);
      candidates.insert(std::make_pair(score, device));
    }
  }

  // Check if the best candidate is suitable at all
  if (!candidates.empty() && candidates.rbegin()->first > 0) {
    physical_device_ = candidates.rbegin()->second;
  } else {
    throw RendererException("Failed to find a suitable GPU");
  }
}

auto VulkanDevice::CreateLogicalDevice() -> void {
  QueueFamilyIndices indices = FindQueueFamilies(physical_device_);

  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<uint32_t> unique_queue_families = {indices.graphics_family.value(),
                                              indices.present_family.value()};

  const float queue_priority = 1.0f;
  for (uint32_t queue_family : unique_queue_families) {
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }

  VkPhysicalDeviceFeatures device_features{};

  VkDeviceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queue_create_infos.data();
  create_info.queueCreateInfoCount =
      static_cast<uint32_t>(queue_create_infos.size());
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount =
      static_cast<uint32_t>(device_extensions_.size());
  create_info.ppEnabledExtensionNames = device_extensions_.data();
  create_info.enabledLayerCount = 0;
  create_info.ppEnabledLayerNames = nullptr;

  if (vkCreateDevice(physical_device_, &create_info, nullptr, &device_) !=
      VK_SUCCESS) {
    throw RendererException("Failed to create logical device");
  }

  vkGetDeviceQueue(device_, indices.graphics_family.value(), 0,
                   &graphics_queue_);
  vkGetDeviceQueue(device_, indices.present_family.value(), 0, &present_queue_);
}

auto VulkanDevice::RateDeviceSuitability(VkPhysicalDevice device) const -> int {
  VkPhysicalDeviceProperties properties{};
  vkGetPhysicalDeviceProperties(device, &properties);

  int score = 0;

  // Discrete GPUs have a significant performance advantage
  if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
    score += 1000;
  }

  // Maximum possible size of textures affects graphics quality
  score += properties.limits.maxImageDimension2D;

  return score;
}

auto VulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)
    -> bool {
  auto available_extensions = GetExtensions(device);

  std::set<std::string, std::less<>> required_extensions(
      device_extensions_.begin(), device_extensions_.end());

  for (const auto &extension : available_extensions) {
    required_extensions.erase(extension.extensionName);
  }

  return required_extensions.empty();
}

auto VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device) -> bool {
  auto indices = FindQueueFamilies(device);

  bool extensions_supported = CheckDeviceExtensionSupport(device);

  bool swap_chain_adequate = false;
  if (extensions_supported) {
    auto swap_chain_support = QuerySwapChainSupport(device);
    swap_chain_adequate = !swap_chain_support.formats.empty() &&
                          !swap_chain_support.present_modes.empty();
  }

  return indices.IsComplete() && extensions_supported && swap_chain_adequate;
}

}  // namespace chr::renderer::internal