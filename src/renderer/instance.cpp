#include "pch.h"
#include "instance.h"

#include "platform.h"
#include "vulkan/vulkan_instance.h"

namespace chr::renderer {

Instance::Instance(const InstanceInfo &info) {
  switch (Platform::type()) {
  case PlatformType::vulkan:
    instance_.template emplace<VulkanInstance>(info);
    break;
  default:
    debug::assert_true(false, "Platform type can't be 'none'");
    break;
  }
}

} // namespace chr::renderer