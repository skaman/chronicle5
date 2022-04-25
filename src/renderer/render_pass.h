// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_RENDER_PASS_H_
#define CHR_RENDERER_RENDER_PASS_H_

#include "common.h"
#include "format.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kRenderPassSize = 16;
}  // namespace internal

struct RenderPassInfo {
  Format format;
};

using RenderPass = Handle<internal::kRenderPassSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_RENDER_PASS_H_