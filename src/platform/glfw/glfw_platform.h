// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_GLFW_PLATFORM_H_
#define CHR_PLATFORM_GLFW_PLATFORM_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "events.h"
#include "platform.h"

namespace chr::internal {

struct GlfwPlatform {
  auto Run() -> int;

 private:
  static auto OnWindowSize(GLFWwindow *window, int width, int height) -> void;
  static auto OnWindowClose(GLFWwindow *window) -> void;
  static auto OnKey(GLFWwindow *window, int key, int scancode, int action,
                    int mods) -> void;
  static auto OnCursorPos(GLFWwindow *window, double x, double y) -> void;
  static auto OnChar(GLFWwindow *window, unsigned int keycode) -> void;
  static auto OnMouseButton(GLFWwindow *window, int button, int action,
                            int mods) -> void;
  static auto OnScroll(GLFWwindow *window, double x_offset, double y_offset)
      -> void;

  GLFWwindow *window_{nullptr};
};

}  // namespace chr::internal

#endif  // CHR_PLATFORM_GLFW_PLATFORM_H_