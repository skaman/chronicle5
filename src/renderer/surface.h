// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SURFACE_H_
#define CHR_RENDERER_SURFACE_H_

#include "pch.h"

namespace chr::renderer {

struct SurfaceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

struct Instance;

struct SurfaceInfo {
  std::function<void *(void *)> custom_init{};
  void *hwnd{nullptr};
};

struct Surface : NonCopyable {
  explicit Surface(const Instance &instance, const SurfaceInfo &info);

  auto test() -> void { surface_->test(); }

 private:
  template <typename Type>
  auto GetNativeType() const -> const Type & {
    return *static_cast<const Type *>(surface_.data());
  }

  entt::basic_poly<SurfaceI, 32> surface_{};

  friend struct Device;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SURFACE_H_