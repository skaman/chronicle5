// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_frame_buffer.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_render_pass.h"

namespace chr::renderer::internal {

VulkanFrameBuffer::VulkanFrameBuffer(const VulkanDevice &device,
                                     const VulkanRenderPass &render_pass,
                                     const FrameBufferCreateInfo &info)
    : device_(device.GetNativeDevice()) {
  std::vector<VkImageView> attachments{};
  attachments.reserve(info.attachments.size());

  for (auto &attachment : info.attachments) {
    auto vulkanImageView = static_cast<VulkanImageView *>(attachment.get());
    attachments.push_back(vulkanImageView->GetNativeImageView());
  }

  VkFramebufferCreateInfo frame_buffer_info{};
  frame_buffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  frame_buffer_info.renderPass = render_pass.GetNativeRenderPass();
  frame_buffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
  frame_buffer_info.pAttachments = attachments.data();
  frame_buffer_info.width = info.extent.x;
  frame_buffer_info.height = info.extent.y;
  frame_buffer_info.layers = 1;

  if (vkCreateFramebuffer(device_, &frame_buffer_info, nullptr,
                          &frame_buffer_) != VK_SUCCESS) {
    frame_buffer_ = VK_NULL_HANDLE;
    throw RendererException("Failed to create framebuffer");
  }
}

VulkanFrameBuffer::~VulkanFrameBuffer() {
  if (frame_buffer_ != VK_NULL_HANDLE) {
    vkDestroyFramebuffer(device_, frame_buffer_, nullptr);
  }
}

}  // namespace chr::renderer::internal