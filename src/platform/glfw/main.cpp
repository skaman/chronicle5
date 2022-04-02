#include <chronicle/common.h>

#include "glfw_platform.h"

auto main() -> int {
  chr::log::set_level(chr::log::level::trace);

  chr::GlfwPlatform platform;
  return platform.run();
}
