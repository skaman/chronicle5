// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "glfw_platform.h"

#include <chronicle/common.h>
#include <chronicle/renderer.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "app.h"
#include "events.h"
#include "glfw_map.h"

namespace chr::platform::internal {

static const std::unordered_map<int, Key> kKeyMap = GetGlfwKeyMap();
static const std::unordered_map<int, MouseButton> kMouseButtonMap =
    GetGlfwMouseButtonMap();

Key GetKeyFromGlfw(int key) {
  if (!kKeyMap.contains(key)) {
    return Key::kUnknown;
  }

  return kKeyMap.at(key);
}

MouseButton GetMouseButtonFromGlfw(int button) {
  if (!kMouseButtonMap.contains(button)) {
    return MouseButton::kUnknown;
  }

  return kMouseButtonMap.at(button);
}

Modifier GetModifiersFromGlfw(int modifiers) {
  Modifier result{};
  if (modifiers & GLFW_MOD_SHIFT) result |= Modifier::kShift;
  if (modifiers & GLFW_MOD_CONTROL) result |= Modifier::kControl;
  if (modifiers & GLFW_MOD_ALT) result |= Modifier::kAlt;
  if (modifiers & GLFW_MOD_SUPER) result |= Modifier::kSuper;
  if (modifiers & GLFW_MOD_CAPS_LOCK) result |= Modifier::kCapsLock;
  if (modifiers & GLFW_MOD_NUM_LOCK) result |= Modifier::kNumLock;

  return result;
}

auto GlfwPlatform::Run() -> int {
  glfwSetErrorCallback([](int error, const char *description) {
    chr::log::Err("GLFW: {0} ({1})", description, error);
  });

  if (!glfwInit()) {
    chr::log::Critical("Cannot initialize GLFW");
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  window_ = glfwCreateWindow(640, 480, "Simple example", nullptr, nullptr);
  if (!window_) {
    chr::log::Critical("Cannot create GLFW main window");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  int width;
  int height;
  int rect_width;
  int rect_height;
  glfwGetWindowSize(window_, &width, &height);
  glfwGetFramebufferSize(window_, &rect_width, &rect_height);

  renderer::InstanceInfo instanceInfo{
      .debug_level{renderer::DebugLevel::kWarning},
      .application_name{"Test application"},
      .engine_name{"Chronicle"}};

  uint32_t extensions_count;
  auto extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
  instanceInfo.required_extensions.reserve(extensions_count);
  for (auto i = 0; i < extensions_count; i++) {
    instanceInfo.required_extensions.emplace_back(extensions[i]);
  }

  renderer::Instance instance{chr::renderer::BackendType::kVulkan,
                              instanceInfo};

  auto window = window_;
  renderer::SurfaceInfo surface_info{.custom_init = [window](void *opaque) {
    VkSurfaceKHR vulkan_surface{VK_NULL_HANDLE};
    glfwCreateWindowSurface(static_cast<VkInstance>(opaque), window, nullptr,
                            &vulkan_surface);
    return vulkan_surface;
  }};

  auto surface = instance.CreateSurface(surface_info);
  auto device = instance.CreateDevice(surface);
  auto swapchain = device.CreateSwapChain(
      surface, {.frame_buffer_width = static_cast<uint32_t>(rect_width),
                .frame_buffer_height = static_cast<uint32_t>(rect_height)});

  entt::locator<Platform>::emplace(instance, surface, device, swapchain);
  auto &platform = entt::locator<Platform>::value();

  auto app_instance = entt::resolve("app"_hs).construct();
  auto &app = app_instance.cast<App &>();

  glfwSetWindowUserPointer(window_, &platform);
  glfwSetWindowSizeCallback(window_, &OnWindowSize);
  glfwSetWindowCloseCallback(window_, &OnWindowClose);
  glfwSetKeyCallback(window_, &OnKey);
  glfwSetCursorPosCallback(window_, &OnCursorPos);
  glfwSetCharCallback(window_, &OnChar);
  glfwSetMouseButtonCallback(window_, &OnMouseButton);
  glfwSetScrollCallback(window_, &OnScroll);

  app.Init();

  while (!glfwWindowShouldClose(window_)) {
    app.Update();

    glfwPollEvents();
  }

  app.Destroy();

  entt::locator<Platform>::reset();

  glfwDestroyWindow(window_);
  glfwTerminate();

  return EXIT_SUCCESS;
}

auto GlfwPlatform::OnWindowSize(GLFWwindow *window, int width, int height)
    -> void {
  debug::Assert(window != nullptr, "window can't be null");

  int rect_width;
  int rect_height;
  glfwGetFramebufferSize(window, &rect_width, &rect_height);

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<WindowSizeEvent>(
      {.width = static_cast<uint32_t>(width),
       .height = static_cast<uint32_t>(height),
       .rect_width = static_cast<uint32_t>(rect_width),
       .rect_height = static_cast<uint32_t>(rect_height)});
}

auto GlfwPlatform::OnWindowClose(GLFWwindow *window) -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<WindowCloseEvent>({});
}

auto GlfwPlatform::OnKey(GLFWwindow *window, int key,
                         [[maybe_unused]] int scancode, int action, int mods)
    -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<KeyEvent>(
      {.key = GetKeyFromGlfw(key),
       .modifiers = GetModifiersFromGlfw(mods),
       .pressed = action != GLFW_RELEASE,
       .repeat = action == GLFW_REPEAT});
}

auto GlfwPlatform::OnCursorPos(GLFWwindow *window, double x, double y) -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<MouseMoveEvent>(
      {.x = static_cast<float>(x), .y = static_cast<float>(y)});
}

auto GlfwPlatform::OnChar(GLFWwindow *window, unsigned int keycode) -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<CharEvent>({.keycode = keycode});
}

auto GlfwPlatform::OnMouseButton(GLFWwindow *window, int button, int action,
                                 int mods) -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<MouseButtonEvent>(
      {.button = GetMouseButtonFromGlfw(button),
       .modifiers = GetModifiersFromGlfw(mods),
       .pressed = action != GLFW_RELEASE});
}

auto GlfwPlatform::OnScroll(GLFWwindow *window, double x_offset,
                            double y_offset) -> void {
  debug::Assert(window != nullptr, "window can't be null");

  auto *platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
  debug::Assert(platform != nullptr, "platform can't be null");

  platform->app_dispatcher_.enqueue<MouseScrollEvent>(
      {.x_offset = static_cast<float>(x_offset),
       .y_offset = static_cast<float>(y_offset)});
}

}  // namespace chr::platform::internal