// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_FRAME_BUFFER_H_
#define CHR_RENDERER_VULKAN_VULKAN_FRAME_BUFFER_H_

#include "frame_buffer.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;
struct VulkanRenderPass;

struct VulkanFrameBuffer : FrameBufferI {
  explicit VulkanFrameBuffer(const VulkanDevice &device,
                             const VulkanRenderPass &render_pass,
                             const FrameBufferCreateInfo &info);

  VulkanFrameBuffer(const VulkanFrameBuffer &) = delete;
  VulkanFrameBuffer(VulkanFrameBuffer &&other) noexcept = delete;

  ~VulkanFrameBuffer() override;

  VulkanFrameBuffer &operator=(const VulkanFrameBuffer &) = delete;
  VulkanFrameBuffer &operator=(VulkanFrameBuffer &&other) = delete;

  auto GetNativeFrameBuffer() const -> VkFramebuffer { return frame_buffer_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkFramebuffer frame_buffer_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_FRAME_BUFFER_H_