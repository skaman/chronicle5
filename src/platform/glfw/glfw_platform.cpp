#include "glfw_platform.h"

#include <chronicle/common.h>

#include "app.h"
#include "events.h"
#include "glfw_map.h"

namespace chr {

static const std::map<const int, const Key> key_map_ = glfw_key_map();
static const std::map<const int, const MouseButton> mouse_button_map_ =
    glfw_mouse_button_map();

Key key_from_glfw(int key) {
  if (!key_map_.contains(key)) {
    return Key::unknown;
  }

  return key_map_.at(key);
}

MouseButton mouse_button_from_glfw(int button) {
  if (!mouse_button_map_.contains(button)) {
    return MouseButton::unknown;
  }

  return mouse_button_map_.at(button);
}

Modifier modifiers_from_glfw(int modifiers) {
  Modifier result{};
  if (modifiers & GLFW_MOD_SHIFT)
    result |= Modifier::shift;
  if (modifiers & GLFW_MOD_CONTROL)
    result |= Modifier::control;
  if (modifiers & GLFW_MOD_ALT)
    result |= Modifier::alt;
  if (modifiers & GLFW_MOD_SUPER)
    result |= Modifier::super;
  if (modifiers & GLFW_MOD_CAPS_LOCK)
    result |= Modifier::caps_lock;
  if (modifiers & GLFW_MOD_NUM_LOCK)
    result |= Modifier::num_lock;

  return result;
}

auto GlfwPlatform::run() -> int {
  glfwSetErrorCallback([](int error, const char *description) {
    chr::log::err("GLFW: {0} ({1})", description, error);
  });

  if (!glfwInit()) {
    chr::log::critical("Cannot initialize GLFW");
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  window_ = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window_) {
    chr::log::critical("Cannot create GLFW main window");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  int width, height, rectWidth, rectHeight;
  glfwGetWindowSize(window_, &width, &height);
  glfwGetFramebufferSize(window_, &rectWidth, &rectHeight);

  auto app_instance = entt::resolve("app"_hs).construct();
  auto &app = app_instance.cast<App &>();

  glfwSetWindowUserPointer(window_, &app);
  glfwSetWindowSizeCallback(window_, &on_window_size);
  glfwSetWindowCloseCallback(window_, &on_window_close);
  glfwSetKeyCallback(window_, &on_key);
  glfwSetCursorPosCallback(window_, &on_cursor_pos);
  glfwSetCharCallback(window_, &on_char);
  glfwSetMouseButtonCallback(window_, &on_mouse_button);
  glfwSetScrollCallback(window_, &on_scroll);

  app.init();

  while (!glfwWindowShouldClose(window_)) {
    app.update();

    glfwPollEvents();
  }

  app.destroy();

  glfwDestroyWindow(window_);
  glfwTerminate();

  return EXIT_SUCCESS;
}

auto GlfwPlatform::on_window_size(GLFWwindow *window, int width, int height)
    -> void {
  int rect_width, rect_height;
  glfwGetFramebufferSize(window, &rect_width, &rect_height);

  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<WindowSizeEvent>(
      {.width = static_cast<uint32_t>(width),
       .height = static_cast<uint32_t>(height),
       .rect_width = static_cast<uint32_t>(rect_width),
       .rect_height = static_cast<uint32_t>(rect_height)});
}

auto GlfwPlatform::on_window_close(GLFWwindow *window) -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<WindowCloseEvent>({});
}

auto GlfwPlatform::on_key(GLFWwindow *window, int key, int scancode, int action,
                          int mods) -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<KeyEvent>(
      {.key = key_from_glfw(key),
       .modifiers = modifiers_from_glfw(mods),
       .pressed = action != GLFW_RELEASE,
       .repeat = action == GLFW_REPEAT});
}

auto GlfwPlatform::on_cursor_pos(GLFWwindow *window, double x, double y)
    -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<MouseMoveEvent>(
      {.x = static_cast<float>(x), .y = static_cast<float>(y)});
}

auto GlfwPlatform::on_char(GLFWwindow *window, unsigned int keycode) -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<CharEvent>({.keycode = keycode});
}

auto GlfwPlatform::on_mouse_button(GLFWwindow *window, int button, int action,
                                   int mods) -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<MouseButtonEvent>(
      {.button = mouse_button_from_glfw(button),
       .modifiers = modifiers_from_glfw(mods),
       .pressed = action != GLFW_RELEASE});
}

auto GlfwPlatform::on_scroll(GLFWwindow *window, double x_offset,
                             double y_offset) -> void {
  auto app = static_cast<App *>(glfwGetWindowUserPointer(window));
  app->platform_.app_dispatcher_.enqueue<MouseScrollEvent>(
      {.x_offset = static_cast<float>(x_offset),
       .y_offset = static_cast<float>(y_offset)});
}

} // namespace chr