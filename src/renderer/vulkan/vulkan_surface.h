// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_SURFACE_H_
#define CHR_RENDERER_VULKAN_VULKAN_SURFACE_H_

#include "pch.h"
#include "surface.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanInstance;

struct VulkanSurface : SurfaceI {
  explicit VulkanSurface(const VulkanInstance &instance,
                         const SurfaceCreateInfo &info);

  VulkanSurface(const VulkanSurface &) = delete;
  VulkanSurface(VulkanSurface &&other) noexcept = delete;

  ~VulkanSurface() override;

  VulkanSurface &operator=(const VulkanSurface &) = delete;
  VulkanSurface &operator=(VulkanSurface &&other) = delete;

  auto GetNativeSurface() const -> VkSurfaceKHR { return surface_; }

 private:
  VkInstance instance_{VK_NULL_HANDLE};
  VkSurfaceKHR surface_{VK_NULL_HANDLE};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_SURFACE_H_