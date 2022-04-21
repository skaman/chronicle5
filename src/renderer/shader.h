// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_H_
#define CHR_RENDERER_SHADER_H_

#include "pch.h"

namespace chr::renderer {

enum class ShaderStage {
  kVertex,
  kFragment,
  kCompute,

  kAllGraphics,
  kAll
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_H_