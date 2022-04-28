// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_IMAGE_VIEW_H_
#define CHR_RENDERER_VULKAN_VULKAN_IMAGE_VIEW_H_

#include "image_view.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanImageView : ImageViewI {
  explicit VulkanImageView(const VulkanDevice &device, const VkFormat format,
                           const VkImage image);

  VulkanImageView(const VulkanImageView &) = delete;
  VulkanImageView(VulkanImageView &&other) noexcept = delete;

  ~VulkanImageView() override;

  VulkanImageView &operator=(const VulkanImageView &) = delete;
  VulkanImageView &operator=(VulkanImageView &&other) = delete;

  auto GetNativeImageView() const -> VkImageView { return image_view_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkImageView image_view_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_IMAGE_VIEW_H_