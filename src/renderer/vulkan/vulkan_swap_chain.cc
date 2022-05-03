// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_swap_chain.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_fence.h"
#include "vulkan_image_view.h"
#include "vulkan_semaphore.h"
#include "vulkan_surface.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanSwapChain::VulkanSwapChain(const VulkanDevice &device,
                                 const VulkanSurface &surface,
                                 const SwapChainCreateInfo &info)
    : device_{device.GetNativeDevice()}, surface_{surface.GetNativeSurface()} {
  auto swap_chain_support =
      device.QuerySwapChainSupport(device.GetPhysicalDevice());

  // TODO: add an exception if swap_chain_support.formats is empty

  auto surface_format = ChooseSwapSurfaceFormat(swap_chain_support.formats);
  auto present_mode = ChooseSwapPresentMode(swap_chain_support.present_modes);
  auto extent = ChooseSwapExtent(swap_chain_support.capabilities,
                                 info.image_size.x, info.image_size.y);

  uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;
  if (swap_chain_support.capabilities.maxImageCount > 0 &&
      image_count > swap_chain_support.capabilities.maxImageCount) {
    image_count = swap_chain_support.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = surface_;
  create_info.minImageCount = image_count;
  create_info.imageFormat = surface_format.format;
  create_info.imageColorSpace = surface_format.colorSpace;
  create_info.imageExtent = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  auto indices = device.FindQueueFamilies(device.GetPhysicalDevice());
  std::array<uint32_t, 2> queue_family_indices = {
      indices.graphics_family.value(), indices.present_family.value()};

  if (indices.graphics_family != indices.present_family) {
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queue_family_indices.data();
  } else {
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0;      // Optional
    create_info.pQueueFamilyIndices = nullptr;  // Optional
  }

  create_info.preTransform = swap_chain_support.capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode = present_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;

  if (auto result =
          vkCreateSwapchainKHR(device_, &create_info, nullptr, &swapchain_);
      result != VK_SUCCESS) {
    throw VulkanException(result, "Failed to create swap chain");
  }

  try {
    CreateSwapChainImages(image_count);
    CreateImageViews(device, image_count, surface_format.format);
  } catch (std::exception) {
    vkDestroySwapchainKHR(device_, swapchain_, nullptr);
    swapchain_ = VK_NULL_HANDLE;
    throw;
  }

  extent_ = {extent.width, extent.height};
  format_ = GetLocalFormat(surface_format.format);
}

VulkanSwapChain::~VulkanSwapChain() {
  if (swapchain_ != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(device_, swapchain_, nullptr);
  }
}

auto VulkanSwapChain::ChooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR> &available_formats)
    -> VkSurfaceFormatKHR {
  debug::Assert(!available_formats.empty(),
                "Available formats list can't be empty");

  for (const auto &available_format : available_formats) {
    if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB &&
        available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return available_format;
    }
  }

  return available_formats[0];
}

auto VulkanSwapChain::ChooseSwapPresentMode(
    const std::vector<VkPresentModeKHR> &available_present_modes)
    -> VkPresentModeKHR {
  for (const auto &available_present_mode : available_present_modes) {
    if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return available_present_mode;
    }
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

auto VulkanSwapChain::ChooseSwapExtent(
    const VkSurfaceCapabilitiesKHR &capabilities, uint32_t frame_buffer_width,
    uint32_t frame_buffer_height) -> VkExtent2D {
  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    VkExtent2D actualExtent = {frame_buffer_width, frame_buffer_height};

    actualExtent.width =
        std::clamp(actualExtent.width, capabilities.minImageExtent.width,
                   capabilities.maxImageExtent.width);
    actualExtent.height =
        std::clamp(actualExtent.height, capabilities.minImageExtent.height,
                   capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

auto VulkanSwapChain::CreateSwapChainImages(uint32_t image_count) -> void {
  if (auto result =
          vkGetSwapchainImagesKHR(device_, swapchain_, &image_count, nullptr);
      result != VK_SUCCESS) {
    throw VulkanException(result, "Failed to create swap chain images");
  }

  images_.resize(image_count);
  if (auto result = vkGetSwapchainImagesKHR(device_, swapchain_, &image_count,
                                            images_.data());
      result != VK_SUCCESS) {
    images_.clear();
    throw VulkanException(result, "Failed to create swap chain images");
  }
}

auto VulkanSwapChain::CreateImageViews(const VulkanDevice &device,
                                       uint32_t image_count,
                                       VkFormat image_format) -> void {
  image_views_.reserve(image_count);
  for (auto i = 0; i < image_count; i++) {
    try {
      image_views_.push_back(std::make_shared<VulkanImageView>(
          device, image_format, images_.at(i)));
    } catch (std::exception) {
      image_views_.clear();
      throw;
    }
  }
}

auto VulkanSwapChain::AcquireNextImage(Semaphore semaphore, Fence fence)
    -> uint32_t {
  VkSemaphore vulkan_semaphore =
      semaphore.get() != nullptr
          ? static_cast<VulkanSemaphore *>(semaphore.get())
                ->GetNativeSemaphore()
          : VK_NULL_HANDLE;

  VkFence vulkan_fence =
      fence.get() != nullptr
          ? static_cast<VulkanFence *>(fence.get())->GetNativeFence()
          : VK_NULL_HANDLE;

  uint32_t image_index;
  vkAcquireNextImageKHR(device_, swapchain_, UINT64_MAX, vulkan_semaphore,
                        vulkan_fence, &image_index);

  return image_index;
}

}  // namespace chr::renderer::internal