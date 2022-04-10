#include "pch.h"

#include "vulkan_surface.h"

#include "vulkan_instance.h"

#if defined(CHR_PLATFORM_WINDOWS)
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#elif defined(CHR_PLATFORM_MACOS)
#include <vulkan/vulkan_macos.h>
#endif

namespace chr::renderer {

VulkanSurface::VulkanSurface(const VulkanInstance &instance,
                             const SurfaceInfo &info)
    : instance_(instance) {
  if (info.init_callback) {
    surface_ = static_cast<VkSurfaceKHR>(
        info.init_callback(instance_.native_instance()));
    if (surface_ == VK_NULL_HANDLE) {
      throw VulkanException("Failed to create window surface");
    }
    return;
  }

  #if defined(CHR_PLATFORM_WINDOWS)
  VkWin32SurfaceCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.hwnd = static_cast<HWND>(info.hwnd);
  createInfo.hinstance = GetModuleHandle(nullptr);
  if (vkCreateWin32SurfaceKHR(instance_.native_instance(), &createInfo, nullptr,
                              &surface_) != VK_SUCCESS) {
    throw VulkanException("Failed to create window surface");
  }
#elif defined(CHR_PLATFORM_MACOS)
  VkMacOSSurfaceCreateInfoMVK createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
  createInfo.pView = surfaceInfo.hwnd;
  if (vkCreateMacOSSurfaceMVK(instance_.native_instance(), &createInfo, nullptr,
                              &surface_) != VK_SUCCESS) {
    throw VulkanException("Failed to create window surface");
  }
#else
#error "Unsupported platform"
#endif
}

VulkanSurface::~VulkanSurface() {
  vkDestroySurfaceKHR(instance_.native_instance(), surface_, nullptr);
}

} // namespace chr::renderer