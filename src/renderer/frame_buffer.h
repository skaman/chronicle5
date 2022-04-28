// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_FRAME_BUFFER_H_
#define CHR_RENDERER_FRAME_BUFFER_H_

#include "common.h"
#include "image_view.h"
#include "render_pass.h"

namespace chr::renderer {

//! @brief Informations used to create a new frame buffer.
struct FrameBufferCreateInfo {
  //! @brief Vector of image views, each of which will be used as the
  //!        corrisponding attachment in a render pass instance.
  std::vector<ImageView> attachments{};

  //! @brief Dimensions of the frame buffer.
  glm::u32vec2 extent{};
};

//! @brief Render passes operate in conjunction with framebuffers. Framebuffers
//!        represent a collection of specific attachments that a render pass
//!        instance uses.
struct FrameBufferI {
  virtual ~FrameBufferI() = default;
};

//! @brief Shared pointer to a FrameBufferI.
using FrameBuffer = std::shared_ptr<FrameBufferI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_FRAME_BUFFER_H_