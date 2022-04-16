// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_EXAMPLE1_EXAMPLE_APP_H_
#define CHR_EXAMPLE1_EXAMPLE_APP_H_

#include <chronicle/common.h>
#include <chronicle/platform.h>
#include <chronicle/storage.h>

struct ExampleApp : chr::platform::App {
  ExampleApp() = default;

  auto Init() -> void override;
  auto Destroy() -> void override;
  auto Update() -> void override;

  auto OnKeyEvent(const chr::platform::KeyEvent &key_event) const -> void;
};

#endif  // CHR_EXAMPLE1_EXAMPLE_APP_H_