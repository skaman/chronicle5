// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SWAPCHAIN_H_
#define CHR_RENDERER_SWAPCHAIN_H_

#include "common.h"
#include "format.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kSwapChainSize = 104;
struct SwapChainI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto GetExtent() const -> glm::u32vec2 {
      return this->template invoke<0>(*this);
    }

    auto GetFormat() const -> Format {
      return this->template invoke<1>(*this);
    }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::GetExtent, &Type::GetFormat>;
};

template <typename T>
concept ConceptSwapChain = std::is_base_of_v<SwapChainI, T>;

struct VulkanInstance;
}  // namespace internal

struct SwapChainInfo {
  uint32_t frame_buffer_width;
  uint32_t frame_buffer_height;
};

struct SwapChain {
  //! @brief The copy constructor is not supported.
  SwapChain(const SwapChain&) = delete;

  //! @brief Move constructor.
  SwapChain(SwapChain&& other) noexcept
      : swapchain_(std::move(other.swapchain_)) {}

  ~SwapChain() = default;

  //! @brief The copy assignment operator is not supported.
  SwapChain& operator=(const SwapChain&) = delete;

  //! @brief Move assignment operator.
  SwapChain& operator=(SwapChain&& other) noexcept {
    std::swap(swapchain_, other.swapchain_);
    return *this;
  }

  auto GetExtent() const -> glm::u32vec2 { return swapchain_->GetExtent(); }
  auto GetFormat() const -> Format { return swapchain_->GetFormat(); }

 private:
  explicit SwapChain() = default;

  template <internal::ConceptSwapChain Type>
  auto Cast() const -> const Type& {
    return *static_cast<const Type*>(swapchain_.data());
  }

  template <internal::ConceptSwapChain Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    swapchain_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::SwapChainI, internal::kSwapChainSize> swapchain_{};

  friend struct internal::VulkanInstance;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SWAPCHAIN_H_