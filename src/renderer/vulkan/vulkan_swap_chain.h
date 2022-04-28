// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_SWAP_CHAIN_H_
#define CHR_RENDERER_VULKAN_VULKAN_SWAP_CHAIN_H_

#include "pch.h"
#include "swap_chain.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;
struct VulkanSurface;

struct VulkanSwapChain : SwapChainI {
  explicit VulkanSwapChain(const VulkanDevice &device,
                           const VulkanSurface &surface,
                           const SwapChainCreateInfo &info);

  VulkanSwapChain(const VulkanSwapChain &) = delete;
  VulkanSwapChain(VulkanSwapChain &&other) noexcept = delete;

  ~VulkanSwapChain() override;

  VulkanSwapChain &operator=(const VulkanSwapChain &) = delete;
  VulkanSwapChain &operator=(VulkanSwapChain &&other) = delete;

  auto GetExtent() const -> glm::u32vec2 override { return extent_; }
  auto GetFormat() const -> Format override { return format_; }
  auto GetImageViewCount() const -> uint32_t override {
    return static_cast<uint32_t>(image_views_.size());
  }
  auto GetImageView(uint32_t index) const -> ImageView override {
    return image_views_.at(index);
  }

  auto GetNativeSwapChain() const -> VkSwapchainKHR { return swapchain_; }

 private:
  static auto ChooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &available_formats)
      -> VkSurfaceFormatKHR;
  static auto ChooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &available_present_modes)
      -> VkPresentModeKHR;
  static auto ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                               uint32_t frame_buffer_width,
                               uint32_t frame_buffer_height) -> VkExtent2D;

  auto CreateSwapChainImages(uint32_t image_count) -> void;
  auto CreateImageViews(const VulkanDevice &device, uint32_t image_count,
                        VkFormat image_format) -> void;

  VkDevice device_{VK_NULL_HANDLE};
  VkSurfaceKHR surface_{VK_NULL_HANDLE};
  VkSwapchainKHR swapchain_{VK_NULL_HANDLE};
  std::vector<VkImage> images_{};
  std::vector<ImageView> image_views_{};
  glm::u32vec2 extent_{};
  Format format_{Format::kUndefined};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_SWAP_CHAIN_H_