// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "log.h"

namespace chr::log {

auto SetLevel(Level level) -> void {
  spdlog::set_level(internal::LevelToSpdlog(level));
}

}  // namespace chr::log