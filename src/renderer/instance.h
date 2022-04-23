// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#pragma once

#ifndef CHR_RENDERER_INSTANCE_H_
#define CHR_RENDERER_INSTANCE_H_

#include "device.h"
#include "pch.h"
#include "shader.h"
#include "surface.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kInstanceSize = 80;

struct InstanceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto CreateSurface(const SurfaceInfo& info) -> Surface {
      return this->template invoke<0>(*this, info);
    }
    auto CreateDevice(const Surface& surface) -> Device {
      return this->template invoke<1>(*this, surface);
    }
    auto CreateShader(const Device& device, const std::vector<uint8_t>& data)
        -> Shader {
      return this->template invoke<2>(*this, device, data);
    }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::CreateSurface, &Type::CreateDevice,
                                &Type::CreateShader>;
};

template <typename T>
concept ConceptInstance = std::is_base_of_v<InstanceI, T>;
}  // namespace internal

//! @brief Debug level for renderer driver.
enum class DebugLevel {
  kNone,     //!< Log nothing.
  kVerbose,  //!< Verbose logging.
  kWarning,  //!< Log only warning and errors.
  kError     //!< Log only errors.
};

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

//! @brief Renderer backend type
enum class BackendType {
  kVulkan  //!< Vulkan renderer.
};

//! @brief Informations used to create a new renderer instance.
struct InstanceInfo {
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

//! @brief The instance will create a connection between your application and
//!        the video driver and it's the main entry point for handle the
//!        creation of the low level graphics objects like surfaces, buffers,
//!        shaders, etc. etc.
struct Instance {
  //! @brief Constructor.
  //! @param type Type of the graphics backend.
  //! @param info Informations used to create a new renderer instance.
  explicit Instance(BackendType type, const InstanceInfo& info);

  //! @brief The copy constructor is not supported.
  Instance(const Instance&) = delete;

  //! @brief Move constructor.
  Instance(Instance&& other) noexcept : instance_(std::move(other.instance_)) {}

  ~Instance() = default;

  //! @brief The copy assignment operator is not supported.
  Instance& operator=(const Instance&) = delete;

  //! @brief Move assignment operator.
  Instance& operator=(Instance&& other) noexcept {
    std::swap(instance_, other.instance_);
    return *this;
  }

  //! @brief Create a surface.
  //! @param info Informations used to create a new surface.
  //! @return The surface.
  auto CreateSurface(const SurfaceInfo& info) -> Surface {
    return instance_->CreateSurface(info);
  }

  //! @brief Create a device.
  //! @param surface Surface where the device need to draw.
  //! @return The device.
  auto CreateDevice(const Surface& surface) -> Device {
    return instance_->CreateDevice(surface);
  }

  //! @brief Create a shader.
  //! @param device Device to use for shader creation.
  //! @param data Shader compiled binary data.
  //! @return Shader module.
  auto CreateShader(const Device& device, const std::vector<uint8_t>& data)
      -> Shader {
    return instance_->CreateShader(device, data);
  }

 private:
  template <internal::ConceptInstance Type>
  auto GetNativeType() const -> const Type& {
    return *static_cast<const Type*>(instance_.data());
  }

  entt::basic_poly<internal::InstanceI, internal::kInstanceSize> instance_{};
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_INSTANCE_H_