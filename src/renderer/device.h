// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_DEVICE_H_
#define CHR_RENDERER_DEVICE_H_

#include "command_buffer.h"
#include "command_pool.h"
#include "common.h"
#include "fence.h"
#include "frame_buffer.h"
#include "pch.h"
#include "pipeline.h"
#include "render_pass.h"
#include "semaphore.h"
#include "shader.h"
#include "surface.h"
#include "swap_chain.h"

namespace chr::renderer {

//! @brief Informations used to queue a submit call.
struct SubmitInfo {
  //! @brief Semaphores upon which to wait before the command buffers for this
  //!        batch begin execution.
  std::vector<Semaphore> wait_semaphores{};

  //! @brief Semaphores which will be signaled when the command buffers for this
  //!        batch have completed execution.
  std::vector<Semaphore> signal_semaphores{};

  //! @brief Command buffers to execute in the batch.
  std::vector<CommandBuffer> command_buffers{};
};

//! @brief Informations used to queu a presentation call.
struct PresentInfo {
  //! @brief Semaphores to wait for before issuing the present request.
  std::vector<Semaphore> wait_semaphores{};

  //! @brief Swapchains to present.
  std::vector<SwapChain> swap_chains{};

  //! @brief Image index ti present.
  uint32_t image_index{0};
};

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

  //! @brief Create a new command pool.
  //! @return A shared pointer to the CommandPoolI instance.
  virtual auto CreateCommandPool() const -> CommandPool = 0;

  //! @brief Create a new command buffer.
  //! @param command_pool Command pool used to create the new command pool
  //! @return A shared pointer to the CommandBufferI instance.
  virtual auto CreateCommandBuffer(const CommandPool& command_pool) const
      -> CommandBuffer = 0;

  //! @brief Create a new semaphore.
  //! @return A shared pointer to the SemaphoreI instance.
  virtual auto CreateSemaphore() const -> Semaphore = 0;

  //! @brief Create a new fence.
  //! @param signaled Create the fence in the signaled state.
  //! @return A shared pointer to the FenceI instance.
  virtual auto CreateFence(bool signaled) const -> Fence = 0;

  //! @brief Queue a submit operation.
  //! @param info Informations used to queue a submit call.
  //! @param fence Fence to be signaled once all submitted command buffers have
  //!              completed execution (optional, can be nullptr).
  virtual auto Submit(const SubmitInfo& info, const Fence& fence) -> void = 0;

  //! @brief Queue a present operation.
  //! @param info Informations used to queue a presentation call.
  virtual auto Present(const PresentInfo& info) -> void = 0;

  //! @brief Wait on the host for the completion of outstanding queue operations
  //!        for all queues on a given logical device.
  virtual auto WaitIdle() -> void = 0;
};

//! @brief Shared pointer to an DeviceI.
using Device = std::shared_ptr<DeviceI>;

}  // namespace chr::renderer

#endif  // CHR_RENDERER_DEVICE_H_