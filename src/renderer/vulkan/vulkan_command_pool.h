// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_COMMAND_POOL_H_
#define CHR_RENDERER_VULKAN_VULKAN_COMMAND_POOL_H_

#include "command_pool.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanDevice;

struct VulkanCommandPool : CommandPoolI {
  explicit VulkanCommandPool(const VulkanDevice &device);

  VulkanCommandPool(const VulkanCommandPool &) = delete;
  VulkanCommandPool(VulkanCommandPool &&other) noexcept = delete;

  ~VulkanCommandPool() override;

  VulkanCommandPool &operator=(const VulkanCommandPool &) = delete;
  VulkanCommandPool &operator=(VulkanCommandPool &&other) = delete;

  auto GetNativeCommandPool() const -> VkCommandPool { return command_pool_; }

 private:
  VkDevice device_{VK_NULL_HANDLE};
  VkCommandPool command_pool_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_COMMAND_POOL_H_