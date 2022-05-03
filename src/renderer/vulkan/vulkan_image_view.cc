// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_image_view.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanImageView::VulkanImageView(const VulkanDevice &device,
                                 const VkFormat format, const VkImage image)
    : device_(device.GetNativeDevice()) {
  VkImageViewCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  create_info.image = image;
  create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  create_info.format = format;
  create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  create_info.subresourceRange.baseMipLevel = 0;
  create_info.subresourceRange.levelCount = 1;
  create_info.subresourceRange.baseArrayLayer = 0;
  create_info.subresourceRange.layerCount = 1;

  if (auto result =
          vkCreateImageView(device_, &create_info, nullptr, &image_view_);
      result != VK_SUCCESS) {
    image_view_ = VK_NULL_HANDLE;
    throw VulkanException(result, "Failed to create image view");
  }
}

VulkanImageView::~VulkanImageView() {
  if (image_view_ != VK_NULL_HANDLE) {
    vkDestroyImageView(device_, image_view_, nullptr);
  }
}

}  // namespace chr::renderer::internal