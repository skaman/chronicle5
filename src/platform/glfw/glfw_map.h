// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_GLFW_MAP_H_
#define CHR_PLATFORM_GLFW_MAP_H_

#include <map>

#include "events.h"

namespace chr::platform::internal {

auto GetGlfwKeyMap() -> std::unordered_map<int, Key>;
auto GetGlfwMouseButtonMap() -> std::unordered_map<int, MouseButton>;

}  // namespace chr

#endif  // CHR_PLATFORM_GLFW_MAP_H_