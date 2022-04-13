// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "instance.h"

#include "platform.h"
#include "vulkan/vulkan_instance.h"

namespace chr::renderer {

Instance::Instance(const InstanceInfo &info) {
  switch (Platform::GetType()) {
    case PlatformType::kVulkan:
      instance_.template emplace<internal::VulkanInstance>(info);
      break;
    default:
      debug::Assert(false, "Platform type can't be 'none'");
      break;
  }
}

}  // namespace chr::renderer