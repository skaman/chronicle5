// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMON_H_
#define CHR_RENDERER_COMMON_H_

#include "pch.h"
#include "enums.h"

//! @brief Renderer API namespace
namespace chr::renderer {

//! @brief Exception that indicate an error communicating with the video card.
struct RendererException : public std::runtime_error {
  using std::runtime_error ::runtime_error;
};

namespace internal {
struct VulkanInstance;
struct VulkanPipeline;
struct VulkanSwapChain;
struct VulkanFrameBuffer;
struct VulkanCommandBuffer;
struct VulkanDevice;
}  // namespace internal

template<size_t Size>
struct Handle {
  //! @brief The copy constructor is not supported.
  Handle(const Handle&) = delete;

  //! @brief Move constructor.
  Handle(Handle&& other) noexcept : handle_(std::move(other.handle_)) {}

  ~Handle() = default;

  //! @brief The copy assignment operator is not supported.
  Handle& operator=(const Handle&) = delete;

  //! @brief Move assignment operator.
  Handle& operator=(Handle&& other) noexcept {
    std::swap(handle_, other.handle_);
    return *this;
  }

 private:
  explicit Handle() = default;

  template <typename Type>
  auto Cast() const -> const Type& {
    return *static_cast<const Type*>(handle_.data());
  }

  template <typename Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    handle_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_any<Size> handle_{};

  friend struct internal::VulkanInstance;
  friend struct internal::VulkanPipeline;
  friend struct internal::VulkanSwapChain;
  friend struct internal::VulkanFrameBuffer;
  friend struct internal::VulkanCommandBuffer;
  friend struct internal::VulkanDevice;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMON_H_