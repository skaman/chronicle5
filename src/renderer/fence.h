// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_FENCE_H_
#define CHR_RENDERER_FENCE_H_

#include "common.h"

namespace chr::renderer {

//! @brief Fence is a synchronization primitive that can be used to insert a
//!        dependency from a queue to the host.
struct FenceI {
  virtual ~FenceI() = default;

  //! @brief Wait for the fence to enter the signaled state.
  virtual auto Wait() -> void = 0;

  //! @brief Set the state of fence to unsignaled.
  virtual auto Reset() -> void = 0;

  //! @brief Get the current state of the fence.
  //! @return Fence status.
  virtual auto GetStatus() -> FenceStatus = 0;
};

//! @brief Shared pointer to a FenceI.
using Fence = std::shared_ptr<FenceI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_FENCE_H_