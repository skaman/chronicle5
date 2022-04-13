#pragma once

#include <chronicle/common.h>
#include <chronicle/platform.h>

struct ExampleApp : chr::App {
  ExampleApp() = default;

  auto Init() -> void override;
  auto Destroy() -> void override;
  auto Update() -> void override;

  auto OnKeyEvent(const chr::KeyEvent &key_event) const -> void;
};
