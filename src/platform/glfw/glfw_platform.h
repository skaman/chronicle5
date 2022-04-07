#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "events.h"
#include "platform.h"

namespace chr {

struct GlfwPlatform {
  auto run() -> int;

private:
  static auto on_window_size(GLFWwindow *window, int width, int height) -> void;
  static auto on_window_close(GLFWwindow *window) -> void;
  static auto on_key(GLFWwindow *window, int key, int scancode, int action,
                     int mods) -> void;
  static auto on_cursor_pos(GLFWwindow *window, double x, double y) -> void;
  static auto on_char(GLFWwindow *window, unsigned int keycode) -> void;
  static auto on_mouse_button(GLFWwindow *window, int button, int action,
                              int mods) -> void;
  static auto on_scroll(GLFWwindow *window, double x_offset, double y_offset)
      -> void;

  GLFWwindow *window_{nullptr};
};

} // namespace chr