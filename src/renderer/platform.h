// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#pragma once

#ifndef CHR_RENDERER_PLATFORM_H_
#define CHR_RENDERER_PLATFORM_H_

namespace chr::renderer {

enum class PlatformType { kNone, kVulkan };

struct Platform {
  static auto GetType() -> PlatformType { return type_; }
  static auto SetType(PlatformType type) -> void { type_ = type; }

 private:
  static PlatformType type_;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_PLATFORM_H_