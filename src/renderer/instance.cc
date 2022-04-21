// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "instance.h"

#include "vulkan/vulkan_instance.h"

namespace chr::renderer {

Instance::Instance(BackendType type, const InstanceInfo &info) {
  switch (type) {
    case BackendType::kVulkan:
      instance_.template emplace<internal::VulkanInstance>(info);
      break;
    default:
      debug::Assert(false, "Platform type can't be 'none'");
      break;
  }
}

}  // namespace chr::renderer