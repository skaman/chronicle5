// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_DEVICE_H_
#define CHR_RENDERER_DEVICE_H_

#include "command_buffer.h"
#include "command_pool.h"
#include "common.h"
#include "frame_buffer.h"
#include "pch.h"
#include "pipeline.h"
#include "render_pass.h"
#include "shader.h"
#include "surface.h"
#include "swap_chain.h"

namespace chr::renderer {

namespace internal {
constexpr size_t kDeviceSize = 80;

struct DeviceI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto CreateShader(const std::vector<uint8_t>& data) -> Shader {
      return this->template invoke<0>(*this, data);
    }

    auto CreateSwapChain(const Surface& surface,
                         const SwapChainInfo& info) const -> SwapChain {
      return this->template invoke<1>(*this, surface, info);
    }

    auto CreatePipeline(const RenderPass& render_pass,
                        const PipelineInfo& info) const -> Pipeline {
      return this->template invoke<2>(*this, render_pass, info);
    }

    auto CreateRenderPass(const RenderPassInfo& info) const -> RenderPass {
      return this->template invoke<3>(*this, info);
    }

    auto CreateFrameBuffer(const RenderPass& render_pass,
                           const FrameBufferInfo& info) const -> FrameBuffer {
      return this->template invoke<4>(*this, render_pass, info);
    }
  };

  template <typename Type>
  using impl = entt::value_list<&Type::CreateShader, &Type::CreateSwapChain,
                                &Type::CreatePipeline, &Type::CreateRenderPass,
                                &Type::CreateFrameBuffer>;
};

template <typename T>
concept ConceptDevice = std::is_base_of_v<DeviceI, T>;

struct VulkanInstance;
}  // namespace internal

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

  auto CreateShader(const std::vector<uint8_t>& data) -> Shader {
    return device_->CreateShader(data);
  }

  auto CreateSwapChain(const Surface& surface, const SwapChainInfo& info) const
      -> SwapChain {
    return device_->CreateSwapChain(surface, info);
  }

  auto CreatePipeline(const RenderPass& render_pass,
                      const PipelineInfo& info) const -> Pipeline {
    return device_->CreatePipeline(render_pass, info);
  }

  auto CreateRenderPass(const RenderPassInfo& info) const -> RenderPass {
    return device_->CreateRenderPass(info);
  }

  auto CreateFrameBuffer(const RenderPass& render_pass,
                         const FrameBufferInfo& info) const -> FrameBuffer {
    return device_->CreateFrameBuffer(render_pass, info);
  }

 private:
  explicit Device() = default;

  template <internal::ConceptDevice Type>
  auto Cast() const -> const Type& {
    return *static_cast<const Type*>(device_.data());
  }

  template <internal::ConceptDevice Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    device_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::DeviceI, internal::kDeviceSize> device_{};

  friend struct internal::VulkanInstance;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_