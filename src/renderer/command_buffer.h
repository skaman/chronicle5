// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_COMMAND_BUFFER_H_
#define CHR_RENDERER_COMMAND_BUFFER_H_

#include "common.h"
#include "frame_buffer.h"
#include "pipeline.h"
#include "render_pass.h"

namespace chr::renderer {

struct BeginRenderPassInfo {
  glm::i32vec2 render_area_offset{};
  glm::u32vec2 render_area_extent{};
  glm::vec4 clear_color{};
};

struct DrawInfo {
  uint32_t vertex_count;
  uint32_t first_vertex;
};

namespace internal {
constexpr size_t kCommandBufferSize = 16;

struct CommandBufferI : entt::type_list<> {
  template <typename Base>
  struct type : Base {
    auto Begin() -> void { this->template invoke<0>(*this); }

    auto End() -> void { this->template invoke<1>(*this); }

    auto BeginRenderPass(const RenderPass& render_pass,
                         const FrameBuffer& frame_buffer,
                         const BeginRenderPassInfo& info) -> void {
      this->template invoke<2>(*this, render_pass, frame_buffer, info);
    }

    auto EndRenderPass() -> void { this->template invoke<3>(*this); }

    auto BindPipeline(const Pipeline& pipeline) -> void {
      this->template invoke<4>(*this, pipeline);
    }

    auto Draw(const DrawInfo& info) -> void {
      this->template invoke<5>(*this, info);
    }
  };

  template <typename Type>
  using impl =
      entt::value_list<&Type::Begin, &Type::End, &Type::BeginRenderPass,
                       &Type::EndRenderPass, &Type::BindPipeline, &Type::Draw>;
};

template <typename T>
concept ConceptCommandBuffer = std::is_base_of_v<CommandBufferI, T>;

struct VulkanDevice;
}  // namespace internal

struct CommandBuffer {
  //! @brief The copy constructor is not supported.
  CommandBuffer(const CommandBuffer&) = delete;

  //! @brief Move constructor.
  CommandBuffer(CommandBuffer&& other) noexcept
      : command_buffer_(std::move(other.command_buffer_)) {}

  ~CommandBuffer() = default;

  //! @brief The copy assignment operator is not supported.
  CommandBuffer& operator=(const CommandBuffer&) = delete;

  //! @brief Move assignment operator.
  CommandBuffer& operator=(CommandBuffer&& other) noexcept {
    std::swap(command_buffer_, other.command_buffer_);
    return *this;
  }

  auto Begin() -> void { command_buffer_->Begin(); }

  auto End() -> void { command_buffer_->End(); }

  auto BeginRenderPass(const RenderPass& render_pass,
                       const FrameBuffer& frame_buffer,
                       const BeginRenderPassInfo& info) -> void {
    command_buffer_->BeginRenderPass(render_pass, frame_buffer, info);
  }

  auto EndRenderPass() -> void { command_buffer_->EndRenderPass(); }

  auto BindPipeline(const Pipeline& pipeline) -> void {
    command_buffer_->BindPipeline(pipeline);
  }

  auto Draw(const DrawInfo& info) -> void { command_buffer_->Draw(info); }

 private:
  explicit CommandBuffer() = default;

  template <internal::ConceptCommandBuffer Type>
  auto Cast() const -> const Type& {
    return *static_cast<const Type*>(command_buffer_.data());
  }

  template <internal::ConceptCommandBuffer Type, typename... Args>
  auto Emplace(Args&&... args) -> void {
    command_buffer_.emplace<Type>(std::forward<Args>(args)...);
  }

  entt::basic_poly<internal::CommandBufferI, internal::kCommandBufferSize>
      command_buffer_{};

  friend struct internal::VulkanDevice;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMAND_BUFFER_H_