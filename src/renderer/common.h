// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMON_H_
#define CHR_RENDERER_COMMON_H_

#include "enums.h"
#include "pch.h"

//! @brief Renderer API namespace
namespace chr::renderer {

//! @brief Exception that indicate an error from the video driver.
struct RendererException : public std::runtime_error {
  explicit RendererException(Error error, const std::string_view message)
      : std::runtime_error(GetErrorMessage(error, message)) {}

 private:
  static auto GetErrorMessage(Error error, const std::string_view message)
      -> std::string {
    return fmt::format("{} (code = {}, message = {})", message,
                       static_cast<int>(error), GetErrorDescription(error));
  }
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMON_H_