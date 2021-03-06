// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_RENDER_PASS_H_
#define CHR_RENDERER_VULKAN_VULKAN_RENDER_PASS_H_

#include "pch.h"
#include "render_pass.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanRenderPass : RenderPassI {
  explicit VulkanRenderPass(const VulkanDevice &device,
                            const RenderPassCreateInfo &info);

  VulkanRenderPass(const VulkanRenderPass &) = delete;
  VulkanRenderPass(VulkanRenderPass &&other) noexcept = delete;

  ~VulkanRenderPass() override;

  VulkanRenderPass &operator=(const VulkanRenderPass &) = delete;
  VulkanRenderPass &operator=(VulkanRenderPass &&other) = delete;

  auto GetNativeRenderPass() const -> VkRenderPass { return render_pass_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkRenderPass render_pass_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_RENDER_PASS_H_