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

  VulkanDevice(const VulkanDevice &) = delete;
  VulkanDevice(VulkanDevice &&other) noexcept
      : instance_{std::move(other.instance_)},
        surface_{std::move(other.surface_)},
        physical_device_{std::move(other.physical_device_)},
        device_{std::move(other.device_)},
        graphics_queue_{std::move(other.graphics_queue_)},
        present_queue_{std::move(other.present_queue_)},
        device_extensions_{std::move(other.device_extensions_)} {
    other.instance_ = VK_NULL_HANDLE;
    other.surface_ = VK_NULL_HANDLE;
    other.physical_device_ = VK_NULL_HANDLE;
    other.device_ = VK_NULL_HANDLE;
    other.graphics_queue_ = VK_NULL_HANDLE;
    other.present_queue_ = VK_NULL_HANDLE;
    other.device_extensions_.clear();
  }

  ~VulkanDevice();

  VulkanDevice &operator=(const VulkanDevice &) = delete;
  VulkanDevice &operator=(VulkanDevice &&other) = delete;

  auto CreateShader(const std::vector<uint8_t> &data) const -> Shader;
  auto CreateSwapChain(const Surface &surface, const SwapChainInfo &info) const
      -> SwapChain;
  auto CreatePipeline(const RenderPass &render_pass,
                      const PipelineInfo &info) const -> Pipeline;
  auto CreateRenderPass(const RenderPassInfo &info) const -> RenderPass;
  auto CreateFrameBuffer(const RenderPass &render_pass,
                         const FrameBufferInfo &info) const -> FrameBuffer;
  auto CreateCommandPool() const -> CommandPool;
  auto CreateCommandBuffer(const CommandPool &command_pool) const
      -> CommandBuffer;

  auto GetPhysicalDevices() const -> std::vector<VkPhysicalDevice>;
  auto GetPhysicalDevice() const -> VkPhysicalDevice {
    return physical_device_;
  }
  auto GetQueueFamilies(VkPhysicalDevice device) const
      -> std::vector<VkQueueFamilyProperties>;
  auto GetExtensions(VkPhysicalDevice device) const
      -> std::vector<VkExtensionProperties>;

  auto FindQueueFamilies(VkPhysicalDevice device) const -> QueueFamilyIndices;
  auto QuerySwapChainSupport(VkPhysicalDevice device) const
      -> SwapChainSupportDetails;

  auto GetNativeDevice() const -> VkDevice { return device_; }

 private:
  auto PickPhysicalDevice() -> void;
  auto CreateLogicalDevice() -> void;

  auto RateDeviceSuitability(VkPhysicalDevice device) const -> int;
  auto CheckDeviceExtensionSupport(VkPhysicalDevice device) -> bool;

  auto IsDeviceSuitable(VkPhysicalDevice device) -> bool;

  VkInstance instance_{VK_NULL_HANDLE};
  VkSurfaceKHR surface_{VK_NULL_HANDLE};
  VkPhysicalDevice physical_device_{VK_NULL_HANDLE};
  VkDevice device_{VK_NULL_HANDLE};
  VkQueue graphics_queue_{VK_NULL_HANDLE};
  VkQueue present_queue_{VK_NULL_HANDLE};

  std::vector<const char *> device_extensions_{};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_DEVICE_H_