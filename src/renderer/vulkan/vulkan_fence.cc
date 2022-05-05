// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_fence.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanFence::VulkanFence(const VulkanDevice &device, bool signaled)
    : device_(device.GetNativeDevice()) {
  CHR_ZONE_SCOPED_VULKAN();

  VkFenceCreateInfo fence_info{};
  fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

  if (auto result = vkCreateFence(device_, &fence_info, nullptr, &fence_);
      result != VK_SUCCESS) {
    fence_ = VK_NULL_HANDLE;
    throw VulkanException(result, "Failed to create fence");
  }
}

VulkanFence::~VulkanFence() {
  CHR_ZONE_SCOPED_VULKAN();

  if (fence_ != VK_NULL_HANDLE) {
    vkDestroyFence(device_, fence_, nullptr);
  }
}

auto VulkanFence::Wait() -> void {
  CHR_ZONE_SCOPED_VULKAN();

  vkWaitForFences(device_, 1, &fence_, VK_TRUE, UINT64_MAX);
}

auto VulkanFence::Reset() -> void {
  CHR_ZONE_SCOPED_VULKAN();

  vkResetFences(device_, 1, &fence_);
}

auto VulkanFence::GetStatus() -> FenceStatus {
  CHR_ZONE_SCOPED_VULKAN();

  switch (vkGetFenceStatus(device_, fence_)) {
    case VK_SUCCESS:
      return FenceStatus::kSignaled;
    case VK_NOT_READY:
      return FenceStatus::kUnsignaled;
    default:
      break;
  }

  return FenceStatus::kUnkwown;
}

}  // namespace chr::renderer::internal