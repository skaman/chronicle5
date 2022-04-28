// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#pragma once

#ifndef CHR_RENDERER_INSTANCE_H_
#define CHR_RENDERER_INSTANCE_H_

#include "device.h"
#include "pch.h"
#include "surface.h"

namespace chr::renderer {

//! @brief Semantic version.
struct Version {
  uint16_t major;  //!< Major.
  uint16_t minor;  //!< Minor.
  uint16_t patch;  //!< Patch.

  //! @brief Default constructor.
  //! @param major Major.
  //! @param minor Minor.
  //! @param patch Patch.
  constexpr Version(uint16_t major, uint16_t minor, uint16_t patch)
      : major{major}, minor{minor}, patch{patch} {}
};

//! @brief Informations used to create a new renderer instance.
struct InstanceCreateInfo {
  //! @brief Renderer debug level.
  DebugLevel debug_level = DebugLevel::kNone;

  //! @brief Required extensions that can be added for specific platforms (the
  //!        usage depended from the backend type).
  std::vector<std::string> required_extensions{};

  //! @brief Application name.
  std::string application_name{};

  //! @brief Application version.
  Version application_version{0, 0, 0};

  //! @brief Engine name.
  std::string engine_name{};

  //! @brief Engine version.
  Version engine_version{0, 0, 0};
};

//! @brief The instance handle a connection between the application and the
//!        video driver and it's the main entry point for handle the creation of
//!        the low level graphics objects like surfaces, buffers, shaders, etc.
//!        etc.
struct InstanceI {
  virtual ~InstanceI() = default;

  //! @brief Create a SurfaceI instance.
  //! @param info Informations used to create a new surface.
  //! @return A shared pointer to the SurfaceI instance.
  virtual auto CreateSurface(const SurfaceCreateInfo& info) -> Surface = 0;

  //! @brief Create a DeviceI instance.
  //! @param surface Surface where the device need to draw.
  //! @return A shared pointer to the DeviceI instance.
  virtual auto CreateDevice(const Surface& surface) -> Device = 0;
};

//! @brief Shared pointer to an InstanceI.
using Instance = std::shared_ptr<InstanceI>;

//! @brief Create a new renderer instance.
//! @param type Type of the graphics backend.
//! @param info Informations used to create a new renderer instance.
//! @return A shared pointer to the InstanceI
auto CreateInstance(BackendType type, const InstanceCreateInfo& info)
    -> Instance;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_INSTANCE_H_