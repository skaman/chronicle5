// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_command_buffer.h"

#include "common.h"
#include "vulkan_command_pool.h"
#include "vulkan_device.h"
#include "vulkan_frame_buffer.h"
#include "vulkan_pipeline.h"
#include "vulkan_render_pass.h"

namespace chr::renderer::internal {

VulkanCommandBuffer::VulkanCommandBuffer(const VulkanDevice &device,
                                         const VulkanCommandPool &command_pool)
    : device_(device.GetNativeDevice()) {
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool.GetNativeCommandPool();
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  if (vkAllocateCommandBuffers(device_, &allocInfo, &command_buffer_) !=
      VK_SUCCESS) {
    command_buffer_ = VK_NULL_HANDLE;
    throw RendererException("Failed to allocate command buffers");
  }
}

auto VulkanCommandBuffer::Begin() -> void {
  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;                   // Optional
  begin_info.pInheritanceInfo = nullptr;  // Optional

  if (vkBeginCommandBuffer(command_buffer_, &begin_info) != VK_SUCCESS) {
    throw RendererException("Failed to begin recording command buffer");
  }
}

auto VulkanCommandBuffer::End() -> void {
  if (vkEndCommandBuffer(command_buffer_) != VK_SUCCESS) {
    throw RendererException("Failed to record command buffer");
  }
}

auto VulkanCommandBuffer::BeginRenderPass(const RenderPass &render_pass,
                                          const FrameBuffer &frame_buffer,
                                          const BeginRenderPassInfo &info)
    -> void {
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass =
      static_cast<VulkanRenderPass *>(render_pass.get())->GetNativeRenderPass();
  renderPassInfo.framebuffer =
      static_cast<VulkanFrameBuffer *>(frame_buffer.get())
          ->GetNativeFrameBuffer();
  renderPassInfo.renderArea.offset = {info.render_area_offset.x,
                                      info.render_area_offset.y};
  renderPassInfo.renderArea.extent = {info.render_area_extent.x,
                                      info.render_area_extent.y};

  std::vector<VkClearValue> clear_values;
  clear_values.reserve(info.clear_colors.size());
  for (auto &clear_color : info.clear_colors) {
    clear_values.push_back(
        {clear_color.r, clear_color.g, clear_color.b, clear_color.a});
  }
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clear_values.size());
  renderPassInfo.pClearValues = clear_values.data();

  vkCmdBeginRenderPass(command_buffer_, &renderPassInfo,
                       VK_SUBPASS_CONTENTS_INLINE);
}

auto VulkanCommandBuffer::EndRenderPass() -> void {
  vkCmdEndRenderPass(command_buffer_);
}

auto VulkanCommandBuffer::BindPipeline(const Pipeline &pipeline) -> void {
  vkCmdBindPipeline(
      command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS,
      static_cast<VulkanPipeline *>(pipeline.get())->GetNativePipeline());
}

auto VulkanCommandBuffer::Draw(const DrawInfo &info) -> void {
  vkCmdDraw(command_buffer_, info.vertex_count, 1, info.first_vertex, 0);
}

}  // namespace chr::renderer::internal