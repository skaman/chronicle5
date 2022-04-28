// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_PIPELINE_H_
#define CHR_RENDERER_PIPELINE_H_

#include "common.h"
#include "shader.h"

namespace chr::renderer {

//! @brief Informations used to create a new pipeline.
struct PipelineCreateInfo {
  //! @brief Shaders attached to the pipeline.
  ShaderSet shader_set{};

  //! @brief Viewport size.
  glm::u32vec2 viewport{};

  //! @brief Scissor size.
  glm::u32vec2 scissor{};
};

//! @brief Pipeline.
struct PipelineI {
  virtual ~PipelineI() = default;
};

//! @brief Shared pointer to an PipelineI.
using Pipeline = std::shared_ptr<PipelineI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_PIPELINE_H_