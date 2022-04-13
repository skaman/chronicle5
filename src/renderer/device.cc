// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "device.h"

#include "platform.h"
#include "vulkan/vulkan_device.h"
#include "vulkan/vulkan_instance.h"
#include "vulkan/vulkan_surface.h"

namespace chr::renderer {

chr::renderer::Device::Device(const Instance &instance,
                              const Surface &surface) {
  switch (Platform::GetType()) {
    case PlatformType::kVulkan:
      device_.template emplace<internal::VulkanDevice>(
          instance.template GetNativeType<internal::VulkanInstance>(),
          surface.template GetNativeType<internal::VulkanSurface>());
      break;
    default:
      debug::Assert(false, "Platform type can't be 'none'");
      break;
  }
}

}  // namespace chr::renderer