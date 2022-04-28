// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_surface.h"

#include "common.h"
#include "vulkan_instance.h"

#if defined(CHR_PLATFORM_WINDOWS)
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#elif defined(CHR_PLATFORM_MACOS)
#include <vulkan/vulkan_macos.h>
#endif

namespace chr::renderer::internal {

VulkanSurface::VulkanSurface(const VulkanInstance &instance,
                             const SurfaceCreateInfo &info)
    : instance_(instance.GetNativeInstance()) {
  if (info.custom_init) {
    surface_ = static_cast<VkSurfaceKHR>(info.custom_init(instance_));
    if (surface_ == VK_NULL_HANDLE) {
      throw RendererException("Failed to create window surface");
    }
    return;
  }

#if defined(CHR_PLATFORM_WINDOWS)
  VkWin32SurfaceCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.hwnd = static_cast<HWND>(info.hwnd);
  createInfo.hinstance = GetModuleHandle(nullptr);
  if (vkCreateWin32SurfaceKHR(instance_, &createInfo, nullptr, &surface_) !=
      VK_SUCCESS) {
    surface_ = VK_NULL_HANDLE;
    throw RendererException("Failed to create window surface");
  }
#elif defined(CHR_PLATFORM_MACOS)
  VkMacOSSurfaceCreateInfoMVK createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
  createInfo.pView = surfaceInfo.hwnd;
  if (vkCreateMacOSSurfaceMVK(instance_, &createInfo, nullptr, &surface_) !=
      VK_SUCCESS) {
    surface_ = VK_NULL_HANDLE;
    throw RendererException("Failed to create window surface");
  }
#else
#error "Unsupported platform"
#endif
}

VulkanSurface::~VulkanSurface() {
  if (surface_ != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(instance_, surface_, nullptr);
  }
}

}  // namespace chr::renderer::internal