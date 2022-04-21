// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SURFACE_H_
#define CHR_RENDERER_SURFACE_H_

#include "pch.h"

namespace chr::renderer {

namespace internal {
struct SurfaceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

template <typename T>
concept ConceptSurface = std::is_base_of_v<SurfaceI, T>;

struct VulkanInstance;
}  // namespace internal

struct Instance;

//! @brief Informations used to create a new surface.
struct SurfaceInfo {
  //! @brief Callback for custom initialization. If this callback is set, the
  //!        internal surface creation is skipped. Instead the callback is
  //!        called. The behaviur of this callback change based on the backend
  //!        type.
  std::function<void *(void *)> custom_init{};

  //! @brief Native window handler where the surface need to be connected.
  void *hwnd{nullptr};
};

//! @brief A surface handle the abstraction that let the system to draw over a
//!        system native window.
struct Surface {
  //! @brief The copy constructor is not supported.
  Surface(const Surface &) = delete;

  //! @brief Move constructor.
  Surface(Surface &&other) noexcept : surface_(std::move(other.surface_)) {}

  ~Surface() = default;

  //! @brief The copy assignment operator is not supported.
  Surface &operator=(const Surface &) = delete;

  //! @brief Move assignment operator.
  Surface &operator=(Surface &&other) noexcept {
    std::swap(surface_, other.surface_);
    return *this;
  }

  auto test() -> void { surface_->test(); }

 private:
  explicit Surface() = default;

  template <typename Type>
  auto GetNativeType() const -> const Type & {
    return *static_cast<const Type *>(surface_.data());
  }

  template <internal::ConceptSurface Type, typename... Args>
  auto Emplace(Args &&...args) -> void {
    surface_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::SurfaceI, 32> surface_{};

  friend struct internal::VulkanInstance;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SURFACE_H_