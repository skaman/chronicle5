// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_DEVICE_H_
#define CHR_RENDERER_DEVICE_H_

#include "common.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kDeviceSize = 80;
}  // namespace internal

//! @brief Logical device that handle communications with the 3D video card.
//!        It automatically pick the best video physical device.
using Device = Handle<internal::kDeviceSize>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_