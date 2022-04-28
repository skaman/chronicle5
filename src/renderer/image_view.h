// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_IMAGE_VIEW_H_
#define CHR_RENDERER_IMAGE_VIEW_H_

#include "common.h"

namespace chr::renderer {

//! @brief Image views representing contiguous ranges of the image subresources
//!        and containing additional metadata are used for that purpose.
struct ImageViewI {
  virtual ~ImageViewI() = default;
};

//! @brief Shared pointer to an ImageViewI.
using ImageView = std::shared_ptr<ImageViewI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_IMAGE_VIEW_H_