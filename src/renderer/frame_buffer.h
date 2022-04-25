// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_FRAME_BUFFER_H_
#define CHR_RENDERER_FRAME_BUFFER_H_

#include "common.h"
#include "image_view.h"
#include "render_pass.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kFrameBufferSize = 16;
}  // namespace internal

struct FrameBufferInfo {
  std::vector<std::reference_wrapper<const ImageView>> attachments{};
  glm::u32vec2 extent{};
};

using FrameBuffer = Handle<internal::kFrameBufferSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_FRAME_BUFFER_H_