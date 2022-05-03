// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_shader.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanShader::VulkanShader(const VulkanDevice &device,
                           const std::vector<uint8_t> &data)
    : device_(device.GetNativeDevice()) {
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = data.size();
  createInfo.pCode = reinterpret_cast<const uint32_t *>(data.data());

  if (auto result =
          vkCreateShaderModule(device_, &createInfo, nullptr, &shader_);
      result != VK_SUCCESS) {
    shader_ = VK_NULL_HANDLE;
    throw VulkanException(result, "Failed to create shader module");
  }
}

VulkanShader::~VulkanShader() {
  if (shader_ != VK_NULL_HANDLE) {
    vkDestroyShaderModule(device_, shader_, nullptr);
  }
}

}  // namespace chr::renderer::internal