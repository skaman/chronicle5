#include "glfw_map.h"

#include "glfw_platform.h"

namespace chr {
auto glfw_key_map() -> std::unordered_map<int, Key> {
  return {
      {GLFW_KEY_SPACE, Key::space},
      {GLFW_KEY_APOSTROPHE, Key::apostrophe},
      {GLFW_KEY_COMMA, Key::comma},
      {GLFW_KEY_MINUS, Key::minus},
      {GLFW_KEY_PERIOD, Key::period},
      {GLFW_KEY_SLASH, Key::slash},
      {GLFW_KEY_0, Key::num_0},
      {GLFW_KEY_1, Key::num_1},
      {GLFW_KEY_2, Key::num_2},
      {GLFW_KEY_3, Key::num_3},
      {GLFW_KEY_4, Key::num_4},
      {GLFW_KEY_5, Key::num_5},
      {GLFW_KEY_6, Key::num_6},
      {GLFW_KEY_7, Key::num_7},
      {GLFW_KEY_8, Key::num_8},
      {GLFW_KEY_9, Key::num_9},
      {GLFW_KEY_SEMICOLON, Key::semicolon},
      {GLFW_KEY_EQUAL, Key::equal},
      {GLFW_KEY_A, Key::a},
      {GLFW_KEY_B, Key::b},
      {GLFW_KEY_C, Key::c},
      {GLFW_KEY_D, Key::d},
      {GLFW_KEY_E, Key::e},
      {GLFW_KEY_F, Key::f},
      {GLFW_KEY_G, Key::g},
      {GLFW_KEY_H, Key::h},
      {GLFW_KEY_I, Key::i},
      {GLFW_KEY_J, Key::j},
      {GLFW_KEY_K, Key::k},
      {GLFW_KEY_L, Key::l},
      {GLFW_KEY_M, Key::m},
      {GLFW_KEY_N, Key::n},
      {GLFW_KEY_O, Key::o},
      {GLFW_KEY_P, Key::p},
      {GLFW_KEY_Q, Key::q},
      {GLFW_KEY_R, Key::r},
      {GLFW_KEY_S, Key::s},
      {GLFW_KEY_T, Key::t},
      {GLFW_KEY_U, Key::u},
      {GLFW_KEY_V, Key::v},
      {GLFW_KEY_W, Key::w},
      {GLFW_KEY_X, Key::x},
      {GLFW_KEY_Y, Key::y},
      {GLFW_KEY_Z, Key::z},
      {GLFW_KEY_LEFT_BRACKET, Key::left_bracket},
      {GLFW_KEY_BACKSLASH, Key::backslash},
      {GLFW_KEY_RIGHT_BRACKET, Key::right_bracket},
      {GLFW_KEY_GRAVE_ACCENT, Key::grace_accent},
      {GLFW_KEY_WORLD_1, Key::world_1},
      {GLFW_KEY_WORLD_2, Key::world_2},
      {GLFW_KEY_ESCAPE, Key::escape},
      {GLFW_KEY_ENTER, Key::enter},
      {GLFW_KEY_TAB, Key::tab},
      {GLFW_KEY_BACKSPACE, Key::backspace},
      {GLFW_KEY_INSERT, Key::insert},
      {GLFW_KEY_DELETE, Key::del},
      {GLFW_KEY_RIGHT, Key::right},
      {GLFW_KEY_LEFT, Key::left},
      {GLFW_KEY_DOWN, Key::down},
      {GLFW_KEY_UP, Key::up},
      {GLFW_KEY_PAGE_UP, Key::page_up},
      {GLFW_KEY_PAGE_DOWN, Key::page_down},
      {GLFW_KEY_HOME, Key::home},
      {GLFW_KEY_END, Key::end},
      {GLFW_KEY_CAPS_LOCK, Key::caps_lock},
      {GLFW_KEY_SCROLL_LOCK, Key::scroll_lock},
      {GLFW_KEY_NUM_LOCK, Key::num_lock},
      {GLFW_KEY_PRINT_SCREEN, Key::print_screen},
      {GLFW_KEY_PAUSE, Key::pause},
      {GLFW_KEY_F1, Key::f1},
      {GLFW_KEY_F2, Key::f2},
      {GLFW_KEY_F3, Key::f3},
      {GLFW_KEY_F4, Key::f4},
      {GLFW_KEY_F5, Key::f5},
      {GLFW_KEY_F6, Key::f6},
      {GLFW_KEY_F7, Key::f7},
      {GLFW_KEY_F8, Key::f8},
      {GLFW_KEY_F9, Key::f9},
      {GLFW_KEY_F10, Key::f10},
      {GLFW_KEY_F11, Key::f11},
      {GLFW_KEY_F12, Key::f12},
      {GLFW_KEY_F13, Key::f13},
      {GLFW_KEY_F14, Key::f14},
      {GLFW_KEY_F15, Key::f15},
      {GLFW_KEY_F16, Key::f16},
      {GLFW_KEY_F17, Key::f17},
      {GLFW_KEY_F18, Key::f18},
      {GLFW_KEY_F19, Key::f19},
      {GLFW_KEY_F20, Key::f20},
      {GLFW_KEY_F21, Key::f21},
      {GLFW_KEY_F22, Key::f22},
      {GLFW_KEY_F23, Key::f23},
      {GLFW_KEY_F24, Key::f24},
      {GLFW_KEY_F25, Key::f25},
      {GLFW_KEY_KP_0, Key::kp_0},
      {GLFW_KEY_KP_1, Key::kp_1},
      {GLFW_KEY_KP_2, Key::kp_2},
      {GLFW_KEY_KP_3, Key::kp_3},
      {GLFW_KEY_KP_4, Key::kp_4},
      {GLFW_KEY_KP_5, Key::kp_5},
      {GLFW_KEY_KP_6, Key::kp_6},
      {GLFW_KEY_KP_7, Key::kp_7},
      {GLFW_KEY_KP_8, Key::kp_8},
      {GLFW_KEY_KP_9, Key::kp_9},
      {GLFW_KEY_KP_DECIMAL, Key::kp_decimal},
      {GLFW_KEY_KP_DIVIDE, Key::kp_divide},
      {GLFW_KEY_KP_MULTIPLY, Key::kp_multiply},
      {GLFW_KEY_KP_SUBTRACT, Key::kp_subtract},
      {GLFW_KEY_KP_ADD, Key::kp_add},
      {GLFW_KEY_KP_ENTER, Key::kp_enter},
      {GLFW_KEY_KP_EQUAL, Key::kp_equal},
      {GLFW_KEY_LEFT_SHIFT, Key::left_shift},
      {GLFW_KEY_LEFT_CONTROL, Key::left_control},
      {GLFW_KEY_LEFT_ALT, Key::left_alt},
      {GLFW_KEY_LEFT_SUPER, Key::left_super},
      {GLFW_KEY_RIGHT_SHIFT, Key::right_shift},
      {GLFW_KEY_RIGHT_CONTROL, Key::right_control},
      {GLFW_KEY_RIGHT_ALT, Key::right_alt},
      {GLFW_KEY_RIGHT_SUPER, Key::right_super},
      {GLFW_KEY_MENU, Key::menu},
  };
}

auto glfw_mouse_button_map() -> std::unordered_map<int, MouseButton> {
  return {
      {GLFW_MOUSE_BUTTON_1, MouseButton::button_1},
      {GLFW_MOUSE_BUTTON_2, MouseButton::button_2},
      {GLFW_MOUSE_BUTTON_3, MouseButton::button_3},
      {GLFW_MOUSE_BUTTON_4, MouseButton::button_4},
      {GLFW_MOUSE_BUTTON_5, MouseButton::button_5},
      {GLFW_MOUSE_BUTTON_6, MouseButton::button_6},
      {GLFW_MOUSE_BUTTON_7, MouseButton::button_7},
      {GLFW_MOUSE_BUTTON_8, MouseButton::button_8},
  };
}

} // namespace chr