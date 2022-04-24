// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_H_
#define CHR_RENDERER_SHADER_H_

#include "common.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kShaderSize = 16;
}  // namespace internal

enum class ShaderStage {
  kVertex,
  kFragment,
  kCompute,

  kAllGraphics,
  kAll
};

using Shader = Handle<internal::kShaderSize>;
using ShaderSet = std::unordered_map<ShaderStage, Shader&>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_H_