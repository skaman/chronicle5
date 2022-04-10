#include "pch.h"

#include "surface.h"

#include "platform.h"
#include "vulkan/vulkan_instance.h"
#include "vulkan/vulkan_surface.h"

namespace chr::renderer {

Surface::Surface(const Instance &instance, const SurfaceInfo &info) {
  switch (Platform::type()) {
  case PlatformType::vulkan:
    surface_.template emplace<VulkanSurface>(
        instance.template native_type<VulkanInstance>(), info);
    break;
  default:
    debug::assert_true(false, "Platform type can't be 'none'");
    break;
  }
}

} // namespace chr::renderer