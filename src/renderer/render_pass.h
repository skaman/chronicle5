// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_RENDER_PASS_H_
#define CHR_RENDERER_RENDER_PASS_H_

#include "common.h"

namespace chr::renderer {

//! @brief Informations used to create a new render pass.
struct RenderPassCreateInfo {
  //! @brief Format used for color attachment.
  Format format;
};

//! @brief A render pass represents a collection of attachments, subpasses, and
//!        dependencies between the subpasses, and describes how the attachments
//!        are used over the course of the subpasses.
struct RenderPassI {
  virtual ~RenderPassI() = default;
};

//! @brief Shared pointer to a RenderPassI.
using RenderPass = std::shared_ptr<RenderPassI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_RENDER_PASS_H_