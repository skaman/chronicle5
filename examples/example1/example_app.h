#pragma once

#include <chronicle/common.h>
#include <chronicle/platform.h>

struct ExampleApp : chr::App {
  ExampleApp() = default;

  auto init() -> void override;
  auto destroy() -> void override;
  auto update() -> void override;

  auto onKeyEvent(const chr::KeyEvent &keyEvent) const -> void;
};
