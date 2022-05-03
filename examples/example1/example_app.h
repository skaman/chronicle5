// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_EXAMPLE1_EXAMPLE_APP_H_
#define CHR_EXAMPLE1_EXAMPLE_APP_H_

#include <chronicle/common.h>
#include <chronicle/platform.h>
#include <chronicle/renderer.h>
#include <chronicle/storage.h>

struct ExampleApp : chr::platform::App {
  ExampleApp() = default;

  auto Init() -> void override;
  auto Destroy() -> void override;
  auto Update() -> void override;

  auto OnKeyEvent(const chr::platform::KeyEvent &key_event) const -> void;

 private:
  chr::renderer::Shader fragment_shader_{};
  chr::renderer::Shader vertex_shader_{};
  chr::renderer::RenderPass render_pass_{};
  std::vector<chr::renderer::FrameBuffer> frame_buffers_{};
  chr::renderer::Pipeline pipeline_{};
  chr::renderer::CommandPool command_pool_{};
  std::vector<chr::renderer::CommandBuffer> command_buffers_{};
  std::vector<chr::renderer::Semaphore> image_available_semaphores_{};
  std::vector<chr::renderer::Semaphore> render_finished_semaphores_{};
  std::vector<chr::renderer::Fence> in_flight_fences_{};
  uint32_t current_frame_{0};

  const uint32_t kMaxFramesInFlight = 2;
};

#endif  // CHR_EXAMPLE1_EXAMPLE_APP_H_