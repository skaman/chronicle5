// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "surface.h"

#include "platform.h"
#include "vulkan/vulkan_instance.h"
#include "vulkan/vulkan_surface.h"

namespace chr::renderer {

Surface::Surface(const Instance &instance, const SurfaceInfo &info) {
  switch (Platform::GetType()) {
    case PlatformType::kVulkan:
      surface_.template emplace<internal::VulkanSurface>(
          instance.template GetNativeType<internal::VulkanInstance>(), info);
      break;
    default:
      debug::Assert(false, "Platform type can't be 'none'");
      break;
  }
}

}  // namespace chr::renderer