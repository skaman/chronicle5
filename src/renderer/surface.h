// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SURFACE_H_
#define CHR_RENDERER_SURFACE_H_

#include "common.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kSurfaceSize = 16;
}  // namespace internal

struct Instance;

//! @brief Informations used to create a new surface.
struct SurfaceInfo {
  //! @brief Callback for custom initialization. If this callback is set, the
  //!        internal surface creation is skipped. Instead the callback is
  //!        called. The behavior of this callback change based on the backend
  //!        type.
  std::function<void *(void *)> custom_init{};

  //! @brief Native window handler where the surface need to be connected.
  void *hwnd{nullptr};
};

//! @brief A surface handle the abstraction that let the system to draw over a
//!        system native window.
using Surface = Handle<internal::kSurfaceSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SURFACE_H_