// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SEMAPHORE_H_
#define CHR_RENDERER_SEMAPHORE_H_

#include "common.h"

namespace chr::renderer {

//! @brief Semaphore is a synchronization primitive that can be used to insert a
//!        dependency between queue operations or between a queue operation and
//!        the host.
struct SemaphoreI {
  virtual ~SemaphoreI() = default;
};

//! @brief Shared pointer to a SemaphoreI.
using Semaphore = std::shared_ptr<SemaphoreI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SEMAPHORE_H_