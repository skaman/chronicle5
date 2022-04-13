// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include <chronicle/common.h>

#include "glfw_platform.h"

auto main() -> int {
  chr::log::SetLevel(chr::log::Level::kTrace);

  chr::internal::GlfwPlatform platform;
  return platform.Run();
}