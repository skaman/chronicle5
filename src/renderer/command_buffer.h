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

//! @brief Informations used to begin a render pass.
struct BeginRenderPassInfo {
  //! @brief Offset of the render area.
  glm::i32vec2 render_area_offset{};

  //! @brief Size of the render area.
  glm::u32vec2 render_area_extent{};

  //! @brief Clear values for eatch attachment defined into FrameBufferI.
  std::vector<glm::vec4> clear_colors{};
};

//! @brief Informations use to record a draw command.
struct DrawInfo {
  //! @brief Number of vertices to draw.
  uint32_t vertex_count;

  //! @brief Index of the first vertex to draw.
  uint32_t first_vertex;
};

//! @brief Command buffers are objects used to record commands which can be
//!        subsequently submitted to a device queue for execution.
struct CommandBufferI {
  virtual ~CommandBufferI() = default;

  //! @brief Begin to recording a command buffer.
  virtual auto Begin() -> void = 0;

  //! @brief Complete to recording a command buffer.
  virtual auto End() -> void = 0;

  //! @brief Begin a render pass instance.
  //! @param render_pass Render pass where to begin the instance.
  //! @param frame_buffer Frame buffer where to begin the instance.
  //! @param info Informations used to begin a render pass.
  virtual auto BeginRenderPass(const RenderPass& render_pass,
                               const FrameBuffer& frame_buffer,
                               const BeginRenderPassInfo& info) -> void = 0;

  //! @brief End a render pass instance.
  virtual auto EndRenderPass() -> void = 0;

  //! @brief Bound the command buffer to a pipeline.
  //! @param pipeline Pipeline to be bound.
  virtual auto BindPipeline(const Pipeline& pipeline) -> void = 0;

  //! @brief Record a non-indexed draw call.
  //! @param info Informations use to record a draw command.
  virtual auto Draw(const DrawInfo& info) -> void = 0;

  //! @brief Reset command buffer.
  virtual auto Reset() -> void = 0;
};

//! @brief Shared pointer to a CommandBufferI.
using CommandBuffer = std::shared_ptr<CommandBufferI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_COMMAND_BUFFER_H_