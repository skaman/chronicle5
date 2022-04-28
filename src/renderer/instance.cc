// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "instance.h"

#include "vulkan/vulkan_instance.h"

namespace chr::renderer {

auto CreateInstance(BackendType type, const InstanceCreateInfo &info)
    -> Instance {
  if (type == BackendType::kVulkan) {
    return std::make_shared<internal::VulkanInstance>(info);
  }

  debug::Assert(false, "Unsupported platform");

  return nullptr;
}

}  // namespace chr::renderer