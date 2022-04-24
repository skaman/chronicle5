// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_PIPELINE_H_
#define CHR_RENDERER_PIPELINE_H_

#include "common.h"
#include "shader.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kPipelineSize = 24;
}  // namespace internal

struct PipelineInfo {
  ShaderSet shader_set{};
  glm::u32vec2 viewport;
  glm::u32vec2 scissor;
};

using Pipeline = Handle<internal::kPipelineSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_PIPELINE_H_