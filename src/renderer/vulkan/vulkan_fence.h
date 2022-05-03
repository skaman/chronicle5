// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_FENCE_H_
#define CHR_RENDERER_VULKAN_VULKAN_FENCE_H_

#include "fence.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanFence : FenceI {
  explicit VulkanFence(const VulkanDevice &device, bool signaled);

  VulkanFence(const VulkanFence &) = delete;
  VulkanFence(VulkanFence &&other) noexcept = delete;

  ~VulkanFence() override;

  VulkanFence &operator=(const VulkanFence &) = delete;
  VulkanFence &operator=(VulkanFence &&other) = delete;

  auto Wait() -> void override;
  auto Reset() -> void override;
  auto GetStatus() -> FenceStatus override;

  auto GetNativeFence() const -> VkFence { return fence_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkFence fence_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_FENCE_H_