// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_DEVICE_H_
#define CHR_RENDERER_VULKAN_VULKAN_DEVICE_H_

#include "device.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct QueueFamilyIndices {
  std::optional<uint32_t> graphics_family{};
  std::optional<uint32_t> present_family{};

  bool IsComplete() const {
    return graphics_family.has_value() && present_family.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

struct VulkanInstance;
struct VulkanSurface;

struct VulkanDevice : DeviceI {
  explicit VulkanDevice(const VulkanInstance &instance,
                        const VulkanSurface &surface);
  ~VulkanDevice();

  auto test() -> void {}

  auto GetPhysicalDevices() const -> std::vector<VkPhysicalDevice>;
  auto GetQueueFamilies(VkPhysicalDevice device) const
      -> std::vector<VkQueueFamilyProperties>;
  auto GetExtensions(VkPhysicalDevice device) const
      -> std::vector<VkExtensionProperties>;

  auto FindQueueFamilies(VkPhysicalDevice device) const -> QueueFamilyIndices;
  auto QuerySwapChainSupport(VkPhysicalDevice device) const
      -> SwapChainSupportDetails;

 private:
  auto PickPhysicalDevice() -> void;
  auto CreateLogicalDevice() -> void;

  auto RateDeviceSuitability(VkPhysicalDevice device) const -> int;
  auto CheckDeviceExtensionSupport(VkPhysicalDevice device) -> bool;

  auto IsDeviceSuitable(VkPhysicalDevice device) -> bool;

  const VulkanInstance &instance_;
  const VulkanSurface &surface_;

  VkPhysicalDevice physical_device_{VK_NULL_HANDLE};
  VkDevice device_{VK_NULL_HANDLE};
  VkQueue graphics_queue_{VK_NULL_HANDLE};
  VkQueue present_queue_{VK_NULL_HANDLE};

  std::vector<const char *> device_extensions_;
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_DEVICE_H_