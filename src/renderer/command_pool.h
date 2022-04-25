// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMAND_POOL_H_
#define CHR_RENDERER_COMMAND_POOL_H_

#include "common.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kCommandPoolSize = 16;
}  // namespace internal

using CommandPool = Handle<internal::kCommandPoolSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMAND_POOL_H_