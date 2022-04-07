#pragma once

#include "events.h"

#include <map>

namespace chr {

auto glfw_key_map() -> std::map<const int, const Key>;
auto glfw_mouse_button_map() -> std::map<const int, const MouseButton>;

} // namespace chr