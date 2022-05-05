// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_semaphore.h"

#include "common.h"
#include "vulkan_device.h"
#include "vulkan_utils.h"

namespace chr::renderer::internal {

VulkanSemaphore::VulkanSemaphore(const VulkanDevice &device)
    : device_(device.GetNativeDevice()) {
  CHR_ZONE_SCOPED_VULKAN();

  VkSemaphoreCreateInfo semaphore_info{};
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  if (auto result =
          vkCreateSemaphore(device_, &semaphore_info, nullptr, &semaphore_);
      result != VK_SUCCESS) {
    semaphore_ = VK_NULL_HANDLE;
    throw VulkanException(result, "Failed to create semaphore");
  }
}

VulkanSemaphore::~VulkanSemaphore() {
  CHR_ZONE_SCOPED_VULKAN();

  if (semaphore_ != VK_NULL_HANDLE) {
    vkDestroySemaphore(device_, semaphore_, nullptr);
  }
}

}  // namespace chr::renderer::internal