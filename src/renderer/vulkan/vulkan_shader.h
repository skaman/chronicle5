// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_SHADER_H_
#define CHR_RENDERER_VULKAN_VULKAN_SHADER_H_

#include "pch.h"
#include "shader.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanShader : ShaderI {
  explicit VulkanShader(const VulkanDevice &device,
                        const std::vector<uint8_t> &data);

  VulkanShader(const VulkanShader &) = delete;
  VulkanShader(VulkanShader &&other) noexcept = delete;

  ~VulkanShader() override;

  VulkanShader &operator=(const VulkanShader &) = delete;
  VulkanShader &operator=(VulkanShader &&other) = delete;

  auto GetNativeShader() const -> VkShaderModule { return shader_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkShaderModule shader_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_SHADER_H_