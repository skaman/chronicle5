// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMAND_POOL_H_
#define CHR_RENDERER_COMMAND_POOL_H_

#include "common.h"

namespace chr::renderer {

//! @brief Command pools allow the implementation to amortize the cost of
//!        resource creation across multiple command buffers.
struct CommandPoolI {
  virtual ~CommandPoolI() = default;
};

//! @brief Shared pointer to a CommandPoolI.
using CommandPool = std::shared_ptr<CommandPoolI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMAND_POOL_H_