#pragma once

#include <entt/entt.hpp>

namespace chr {

enum class Key {
  unknown,
  space,
  apostrophe,
  comma,
  minus,
  period,
  slash,
  num_0,
  num_1,
  num_2,
  num_3,
  num_4,
  num_5,
  num_6,
  num_7,
  num_8,
  num_9,
  semicolon,
  equal,
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  left_bracket,
  backslash,
  right_bracket,
  grace_accent,
  world_1,
  world_2,
  escape,
  enter,
  tab,
  backspace,
  insert,
  del,
  right,
  left,
  down,
  up,
  page_up,
  page_down,
  home,
  end,
  caps_lock,
  scroll_lock,
  num_lock,
  print_screen,
  pause,
  f1,
  f2,
  f3,
  f4,
  f5,
  f6,
  f7,
  f8,
  f9,
  f10,
  f11,
  f12,
  f13,
  f14,
  f15,
  f16,
  f17,
  f18,
  f19,
  f20,
  f21,
  f22,
  f23,
  f24,
  f25,
  kp_0,
  kp_1,
  kp_2,
  kp_3,
  kp_4,
  kp_5,
  kp_6,
  kp_7,
  kp_8,
  kp_9,
  kp_decimal,
  kp_divide,
  kp_multiply,
  kp_subtract,
  kp_add,
  kp_enter,
  kp_equal,
  left_shift,
  left_control,
  left_alt,
  left_super,
  right_shift,
  right_control,
  right_alt,
  right_super,
  menu
};

enum class Modifier {
  shift = 1,
  control = 2,
  alt = 4,
  super = 8,
  caps_lock = 16,
  num_lock = 32,

  _entt_enum_as_bitmask = 128
};

enum class MouseButton {
  unknown = 0,
  button_1 = 1,
  button_2 = 2,
  button_3 = 3,
  button_4 = 4,
  button_5 = 5,
  button_6 = 6,
  button_7 = 7,
  button_8 = 8,

  buttonLeft = button_1,
  buttonRight = button_2,
  buttonMiddle = button_3
};

struct Event {};

struct KeyEvent : Event {
  Key key;
  Modifier modifiers;
  bool pressed;
  bool repeat;
};

struct CharEvent : Event {
  uint32_t keycode;
};

struct MouseMoveEvent : Event {
  float x;
  float y;
};

struct MouseButtonEvent : Event {
  MouseButton button;
  Modifier modifiers;
  bool pressed;
};

struct MouseScrollEvent : Event {
  float x_offset;
  float y_offset;
};

struct WindowSizeEvent : Event {
  uint32_t width;
  uint32_t height;
  uint32_t rect_width;
  uint32_t rect_height;
};

struct WindowCloseEvent : Event {};

struct ShouldCloseEvent : Event {};

} // namespace chr