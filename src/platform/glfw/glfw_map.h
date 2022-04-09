#pragma once

#include "events.h"

#include <map>

namespace chr {

auto glfw_key_map() -> std::unordered_map<int, Key>;
auto glfw_mouse_button_map() -> std::unordered_map<int, MouseButton>;

} // namespace chr