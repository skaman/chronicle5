#pragma once

#include "vulkan_pch.h"

#include "surface.h"

namespace chr::renderer {

struct VulkanInstance;

struct VulkanSurface : SurfaceI {
  explicit VulkanSurface(const VulkanInstance &instance,
                         const SurfaceInfo &info);
  ~VulkanSurface();

  auto test() -> void {}

private:
  const VulkanInstance &instance_;

  VkSurfaceKHR surface_{VK_NULL_HANDLE};
};

} // namespace chr::renderer