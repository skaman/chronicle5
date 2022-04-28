// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_PIPELINE_H_
#define CHR_RENDERER_VULKAN_VULKAN_PIPELINE_H_

#include "pch.h"
#include "pipeline.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;
struct VulkanRenderPass;

struct VulkanPipeline : PipelineI {
  explicit VulkanPipeline(const VulkanDevice &device,
                          const VulkanRenderPass &render_pass,
                          const PipelineCreateInfo &info);

  VulkanPipeline(const VulkanPipeline &) = delete;
  VulkanPipeline(VulkanPipeline &&other) noexcept = delete;

  ~VulkanPipeline() override;

  VulkanPipeline &operator=(const VulkanPipeline &) = delete;
  VulkanPipeline &operator=(VulkanPipeline &&other) = delete;

  auto GetNativePipeline() const -> VkPipeline { return pipeline_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkPipelineLayout pipeline_layout_{VK_NULL_HANDLE};
  VkPipeline pipeline_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_PIPELINE_H_