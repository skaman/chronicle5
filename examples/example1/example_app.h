#pragma once

#include <chronicle/common.h>
#include <chronicle/platform.h>

struct ExampleApp : chr::App {
  ExampleApp() {}

  virtual auto init() -> void override;
  virtual auto destroy() -> void override;
  virtual auto update() -> void override;

  auto onKeyEvent(const chr::KeyEvent &keyEvent) -> void;
};

const auto app = chr::register_app<ExampleApp>();