// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#pragma once

#ifndef CHR_RENDERER_INSTANCE_H_
#define CHR_RENDERER_INSTANCE_H_

#include "pch.h"

namespace chr::renderer {

enum class DebugLevel { kNone, kVerbose, kWarning, kError };

struct Version {
  uint16_t major;
  uint16_t minor;
  uint16_t patch;

  constexpr Version(uint16_t major, uint16_t minor, uint16_t patch)
      : major{major}, minor{minor}, patch{patch} {}
};

struct InstanceInfo {
  DebugLevel debug_level = DebugLevel::kNone;
  std::vector<std::string> required_extensions{};
  std::string application_name{};
  Version application_version{0, 0, 0};
  std::string engine_name{};
  Version engine_version{0, 0, 0};
};

struct InstanceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

struct Instance : NonCopyable {
  explicit Instance(const InstanceInfo &info);

  auto test() -> void { instance_->test(); }

 private:
  template <typename Type>
  auto GetNativeType() const -> const Type & {
    return *static_cast<const Type *>(instance_.data());
  }

  entt::basic_poly<InstanceI, 32> instance_{};

  friend struct Surface;
  friend struct Device;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_INSTANCE_H_