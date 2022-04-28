// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define CHR_RENDERER_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "command_buffer.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;
struct VulkanCommandPool;

struct VulkanCommandBuffer : CommandBufferI {
  explicit VulkanCommandBuffer(const VulkanDevice &device,
                               const VulkanCommandPool &command_pool);

  VulkanCommandBuffer(const VulkanCommandBuffer &) = delete;
  VulkanCommandBuffer(VulkanCommandBuffer &&other) noexcept = delete;

  VulkanCommandBuffer &operator=(const VulkanCommandBuffer &) = delete;
  VulkanCommandBuffer &operator=(VulkanCommandBuffer &&other) = delete;

  auto Begin() -> void override;
  auto End() -> void override;
  auto BeginRenderPass(const RenderPass &render_pass,
                       const FrameBuffer &frame_buffer,
                       const BeginRenderPassInfo &info) -> void override;
  auto EndRenderPass() -> void override;
  auto BindPipeline(const Pipeline &pipeline) -> void override;
  auto Draw(const DrawInfo &info) -> void override;

  auto GetNativeCommandBuffer() const -> VkCommandBuffer {
    return command_buffer_;
  }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkCommandBuffer command_buffer_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_COMMAND_BUFFER_H_