// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_command_pool.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanCommandPool::VulkanCommandPool(const VulkanDevice &device)
    : device_(device.GetNativeDevice()) {
  auto queueFamilyIndices =
      device.FindQueueFamilies(device.GetPhysicalDevice());

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphics_family.value();

  if (auto result =
          vkCreateCommandPool(device_, &poolInfo, nullptr, &command_pool_);
      result != VK_SUCCESS) {
    command_pool_ = VK_NULL_HANDLE;
    throw VulkanException(result, "Failed to create command pool");
  }
}

VulkanCommandPool::~VulkanCommandPool() {
  if (command_pool_ != VK_NULL_HANDLE) {
    vkDestroyCommandPool(device_, command_pool_, nullptr);
  }
}

}  // namespace chr::renderer::internal