// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_H_
#define CHR_RENDERER_SHADER_H_

#include "pch.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kShaderSize = 16;

struct ShaderI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::test>;
};

template <typename T>
concept ConceptShader = std::is_base_of_v<ShaderI, T>;

struct VulkanInstance;
}  // namespace internal

enum class ShaderStage {
  kVertex,
  kFragment,
  kCompute,

  kAllGraphics,
  kAll
};

struct Shader {
  //! @brief The copy constructor is not supported.
  Shader(const Shader&) = delete;

  //! @brief Move constructor.
  Shader(Shader&& other) noexcept : shader_(std::move(other.shader_)) {}

  ~Shader() = default;

  //! @brief The copy assignment operator is not supported.
  Shader& operator=(const Shader&) = delete;

  //! @brief Move assignment operator.
  Shader& operator=(Shader&& other) noexcept {
    std::swap(shader_, other.shader_);
    return *this;
  }

  auto test() -> void { shader_->test(); }

 private:
  explicit Shader() = default;

  template <internal::ConceptShader Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    shader_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::ShaderI, internal::kShaderSize> shader_{};

  friend struct internal::VulkanInstance;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_H_