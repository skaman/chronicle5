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

  VulkanShader(VulkanShader &&other) noexcept
      : device_{other.device_}, shader_{other.shader_} {
    other.shader_ = VK_NULL_HANDLE;
  }

  ~VulkanShader();

  VulkanShader &operator=(const VulkanShader &) = delete;
  VulkanShader &operator=(VulkanShader &&other) = delete;

  auto test() -> void {}

  auto GetNativeShader() const -> VkShaderModule { return shader_; }

 private:
  const VulkanDevice &device_;

  VkShaderModule shader_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_SHADER_H_