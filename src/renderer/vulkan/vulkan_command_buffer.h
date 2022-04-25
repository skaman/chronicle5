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

  VulkanCommandBuffer(VulkanCommandBuffer &&other) noexcept
      : device_{other.device_}, command_buffer_{other.command_buffer_} {
    other.device_ = VK_NULL_HANDLE;
    other.command_buffer_ = VK_NULL_HANDLE;
  }

  ~VulkanCommandBuffer() = default;

  VulkanCommandBuffer &operator=(const VulkanCommandBuffer &) = delete;
  VulkanCommandBuffer &operator=(VulkanCommandBuffer &&other) = delete;

  auto Begin() -> void;
  auto End() -> void;

  auto BeginRenderPass(const RenderPass &render_pass,
                       const FrameBuffer &frame_buffer,
                       const BeginRenderPassInfo &info) -> void;
  auto EndRenderPass() -> void;
  auto BindPipeline(const Pipeline &pipeline) -> void;
  auto Draw(const DrawInfo& info) -> void;

  auto GetNativeCommandBuffer() const -> VkCommandBuffer {
    return command_buffer_;
  }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkCommandBuffer command_buffer_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_COMMAND_BUFFER_H_