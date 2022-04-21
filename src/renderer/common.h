// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMON_H_
#define CHR_RENDERER_COMMON_H_

namespace chr::renderer {

//! @brief Exception that indicate an error communicating with the video card.
struct RendererException : public std::runtime_error {
  using std::runtime_error ::runtime_error;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMON_H_