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

//! @brief Logical device that handle the connection with the physical device.
//!        The physical device is automatically picked up from available devices
//!        trying to guess the most performant one.
struct DeviceI {
  virtual ~DeviceI() = default;

  //! @brief Create a new shader modules.
  //! @param data Shader binary data (already compiled).
  //! @return A shared pointer to the ShaderI instance.
  virtual auto CreateShader(const std::vector<uint8_t>& data) const
      -> Shader = 0;

  //! @brief Create a new swapchain.
  //! @param surface Surface used for create the swapchain.
  //! @param info Informations used to create a new swapchain.
  //! @return A shared pointer to the SwapChainI instance.
  virtual auto CreateSwapChain(const Surface& surface,
                               const SwapChainCreateInfo& info) const
      -> SwapChain = 0;

  //! @brief Create a new pipeline.
  //! @param render_pass Render pass used to create the new pipeline.
  //! @param info Informations used to create a new pipeline.
  //! @return A shared pointer to the PipelineI instance.
  virtual auto CreatePipeline(const RenderPass& render_pass,
                              const PipelineCreateInfo& info) const
      -> Pipeline = 0;

  //! @brief Create a new render pass.
  //! @param info Informations used to create a new render pass.
  //! @return A shared pointer to the RenderPassI instance.
  virtual auto CreateRenderPass(const RenderPassCreateInfo& info) const
      -> RenderPass = 0;

  //! @brief Create a new frame buffer.
  //! @param render_pass Render pass used to create the new frame buffer.
  //! @param info Informations used to create a new frame buffer.
  //! @return A shared pointer to the FrameBufferI instance.
  virtual auto CreateFrameBuffer(const RenderPass& render_pass,
                                 const FrameBufferCreateInfo& info) const
      -> FrameBuffer = 0;

  //! @brief Create a new command buffer.
  //! @param command_pool Command pool used to create the new command pool
  //! @return A shared pointer to the CommandBufferI instance.
  virtual auto CreateCommandBuffer(const CommandPool& command_pool) const
      -> CommandBuffer = 0;
};

//! @brief Shared pointer to an DeviceI.
using Device = std::shared_ptr<DeviceI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_