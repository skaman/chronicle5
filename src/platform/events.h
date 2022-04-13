// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_EVENTS_H_
#define CHR_PLATFORM_EVENTS_H_

#include <entt/entt.hpp>

namespace chr::platform {

enum class Key {
  kUnknown,
  kSpace,
  kApostrophe,
  kComma,
  kMinus,
  kPeriod,
  kSlash,
  k0,
  k1,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  kSemicolon,
  kEqual,
  kA,
  kB,
  kC,
  kD,
  kE,
  kF,
  kG,
  kH,
  kI,
  kJ,
  kK,
  kL,
  kM,
  kN,
  kO,
  kP,
  kQ,
  kR,
  kS,
  kT,
  kU,
  kV,
  kW,
  kX,
  kY,
  kZ,
  kLeftBracket,
  kBackSlash,
  kRightBracket,
  kGraceAccent,
  kWorld1,
  kWorld2,
  kEscape,
  kEnter,
  kTab,
  kBackspace,
  kInsert,
  kDel,
  kRight,
  kLeft,
  kDown,
  kUp,
  kPageUp,
  kPageDown,
  kHome,
  kEnd,
  kCapsLock,
  kScrollLock,
  kNumLock,
  kPrintScreen,
  kPause,
  kF1,
  kF2,
  kF3,
  kF4,
  kF5,
  kF6,
  kF7,
  kF8,
  kF9,
  kF10,
  kF11,
  kF12,
  kF13,
  kF14,
  kF15,
  kF16,
  kF17,
  kF18,
  kF19,
  kF20,
  kF21,
  kF22,
  kF23,
  kF24,
  kF25,
  kKp0,
  kKp1,
  kKp2,
  kKp3,
  kKp4,
  kKp5,
  kKp6,
  kKp7,
  kKp8,
  kKp9,
  kKpDecimal,
  kKpDivide,
  kKpMultiply,
  kKpSubtract,
  kKpAdd,
  kKpEnter,
  kKpEqual,
  kLeftShift,
  kLeftControl,
  kLeftAlt,
  kLeftSuper,
  kRightShift,
  kRightControl,
  kRightAlt,
  kRightSuper,
  kMenu
};

enum class Modifier {
  kShift = 1,
  kControl = 2,
  kAlt = 4,
  kSuper = 8,
  kCapsLock = 16,
  kNumLock = 32,

  _entt_enum_as_bitmask = 128
};

enum class MouseButton {
  kUnknown = 0,
  kButton1 = 1,
  kButton2 = 2,
  kButton3 = 3,
  kButton4 = 4,
  kButton5 = 5,
  kButton6 = 6,
  kButton7 = 7,
  kButton8 = 8,

  kButtonLeft = kButton1,
  kButtonRight = kButton2,
  kButtonMiddle = kButton3
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

}  // namespace chr

#endif  // CHR_PLATFORM_EVENTS_H_