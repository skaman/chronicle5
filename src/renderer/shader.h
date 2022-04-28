// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_H_
#define CHR_RENDERER_SHADER_H_

#include "common.h"

namespace chr::renderer {

//! @brief Shader module.
struct ShaderI {
  virtual ~ShaderI() = default;
};

//! @brief Shared pointer to a ShaderI.
using Shader = std::shared_ptr<ShaderI>;

//! @brief A set of shaders (one for desired stage).
using ShaderSet = std::unordered_map<ShaderStage, Shader>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_H_