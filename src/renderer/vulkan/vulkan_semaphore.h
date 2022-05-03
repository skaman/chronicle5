// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_SEMAPHORE_H_
#define CHR_RENDERER_VULKAN_VULKAN_SEMAPHORE_H_

#include "pch.h"
#include "semaphore.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanSemaphore : SemaphoreI {
  explicit VulkanSemaphore(const VulkanDevice &device);

  VulkanSemaphore(const VulkanSemaphore &) = delete;
  VulkanSemaphore(VulkanSemaphore &&other) noexcept = delete;

  ~VulkanSemaphore() override;

  VulkanSemaphore &operator=(const VulkanSemaphore &) = delete;
  VulkanSemaphore &operator=(VulkanSemaphore &&other) = delete;

  auto GetNativeSemaphore() const -> VkSemaphore { return semaphore_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkSemaphore semaphore_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_SEMAPHORE_H_