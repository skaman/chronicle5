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
                           const SwapChainInfo &info);

  VulkanSwapChain(const VulkanSwapChain &) = delete;

  VulkanSwapChain(VulkanSwapChain &&other) noexcept
      : device_{other.device_},
        surface_{other.surface_},
        swapchain_{other.swapchain_},
        images_{other.images_},
        image_views_{std::move(other.image_views_)},
        extent_{other.extent_},
        format_{other.format_} {
    other.device_ = VK_NULL_HANDLE;
    other.surface_ = VK_NULL_HANDLE;
    other.swapchain_ = VK_NULL_HANDLE;
    other.images_.clear();
    other.image_views_.clear();
    other.extent_ = {};
    other.format_ = Format::kUndefined;
  }

  ~VulkanSwapChain();

  VulkanSwapChain &operator=(const VulkanSwapChain &) = delete;
  VulkanSwapChain &operator=(VulkanSwapChain &&other) = delete;

  auto GetNativeSwapChain() const -> VkSwapchainKHR { return swapchain_; }

  auto GetExtent() const -> glm::u32vec2 { return extent_; }
  auto GetFormat() const -> Format { return format_; }

  auto GetImageViewCount() const -> uint32_t {
    return static_cast<uint32_t>(image_views_.size());
  }
  auto GetImageView(uint32_t index) const -> const ImageView & {
    return image_views_.at(index);
  }

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