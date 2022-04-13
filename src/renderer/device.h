// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_DEVICE_H_
#define CHR_RENDERER_DEVICE_H_

#include "pch.h"

namespace chr::renderer {

struct DeviceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

struct Instance;
struct Surface;

struct Device : NonCopyable {
  explicit Device(const Instance &instance, const Surface &surface);

  auto test() -> void { device_->test(); }

 private:
  entt::basic_poly<DeviceI, 32> device_{};
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_