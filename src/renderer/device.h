// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_DEVICE_H_
#define CHR_RENDERER_DEVICE_H_

#include "pch.h"

namespace chr::renderer {

namespace internal {
struct DeviceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

template <typename T>
concept ConceptDevice = std::is_base_of_v<DeviceI, T>;

struct VulkanInstance;
}  // namespace internal

struct Instance;
struct Surface;

//! @brief Logical device that handle communications with the 3D video card.
//!        It automatically pick the best video physical device.
struct Device {
  //! @brief The copy constructor is not supported.
  Device(const Device&) = delete;

  //! @brief Move constructor.
  Device(Device&& other) noexcept : device_(std::move(other.device_)) {}

  ~Device() = default;

  //! @brief The copy assignment operator is not supported.
  Device& operator=(const Device&) = delete;

  //! @brief Move assignment operator.
  Device& operator=(Device&& other) noexcept {
    std::swap(device_, other.device_);
    return *this;
  }

  auto test() -> void { device_->test(); }

 private:
  explicit Device() = default;

  template <internal::ConceptDevice Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    device_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::DeviceI, 32> device_{};

  friend struct internal::VulkanInstance;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_