// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SWAP_CHAIN_H_
#define CHR_RENDERER_SWAP_CHAIN_H_

#include "common.h"
#include "image_view.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kSwapChainSize = 104;

struct SwapChainI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto GetExtent() const -> glm::u32vec2 {
      return this->template invoke<0>(*this);
    }

    auto GetFormat() const -> Format { return this->template invoke<1>(*this); }

    auto GetImageViewCount() const -> uint32_t {
      return this->template invoke<2>(*this);
    }
    auto GetImageView(uint32_t index) const -> const ImageView& {
      return this->template invoke<3>(*this, index);
    }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::GetExtent, &Type::GetFormat,
                                &Type::GetImageViewCount, &Type::GetImageView>;
};

template <typename T>
concept ConceptSwapChain = std::is_base_of_v<SwapChainI, T>;

struct VulkanInstance;
struct VulkanDevice;
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

  auto GetImageViewCount() const -> uint32_t {
    return swapchain_->GetImageViewCount();
  }
  auto GetImageView(uint32_t index) const -> const ImageView& {
    return swapchain_->GetImageView(index);
  }

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
  friend struct internal::VulkanDevice;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SWAP_CHAIN_H_