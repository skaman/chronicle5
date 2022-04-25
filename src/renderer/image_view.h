// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_IMAGE_VIEW_H_
#define CHR_RENDERER_IMAGE_VIEW_H_

#include "common.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kImageViewSize = 16;
}  // namespace internal

using ImageView = Handle<internal::kImageViewSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_IMAGE_VIEW_H_