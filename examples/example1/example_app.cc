// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "example_app.h"

CHR_INIT { chr::platform::RegisterApp<ExampleApp>(); }

auto ExampleApp::Init() -> void {
  CHR_ZONE_SCOPED();

  chr::log::Info("init");
  auto& platform = entt::locator<chr::platform::Platform>::value();

  platform.template Connect<chr::platform::KeyEvent, &ExampleApp::OnKeyEvent>(
      this);

  chr::storage::Storage storage{chr::storage::BackendType::kFileSystem};
  storage.SetBasePath("../assets");

  for (auto const& entry : storage.GetEntries("/")) {
    chr::log::Info("{} - {} - {} - {} - {}", entry.Name(), entry.IsDirectory(),
                   entry.Extension(), entry.HaveExtension(), entry.Size());
  }

  auto triangle_shader_frag = storage.GetFile("/triangle_shader.frag");
  triangle_shader_frag.Open();
  auto triangle_shader_frag_data = triangle_shader_frag.ReadAll();
  triangle_shader_frag.Close();

  auto triangle_shader_vert = storage.GetFile("/triangle_shader.vert");
  triangle_shader_vert.Open();
  auto triangle_shader_vert_data = triangle_shader_vert.ReadAll();
  triangle_shader_vert.Close();

  chr::renderer::ShaderCompiler compiler{};

  auto fragment_shader_compiled =
      compiler.Compile(triangle_shader_frag_data, "triangle_shader.frag",
                       chr::renderer::ShaderStage::kFragment);

  auto vertex_shader_compiled =
      compiler.Compile(triangle_shader_vert_data, "triangle_shader.vert",
                       chr::renderer::ShaderStage::kVertex);

  const auto& device = platform.GetDevice();
  const auto& swap_chain = platform.GetSwapChain();

  auto swap_chain_extent = swap_chain->GetExtent();
  auto swap_chain_format = swap_chain->GetFormat();

  fragment_shader_ = device->CreateShader(fragment_shader_compiled.data);
  vertex_shader_ = device->CreateShader(vertex_shader_compiled.data);

  render_pass_ = device->CreateRenderPass({.format = swap_chain_format});

  auto swap_chain_image_view_count = swap_chain->GetImageViewCount();
  frame_buffers_.reserve(swap_chain_image_view_count);
  for (auto i = 0; i < swap_chain_image_view_count; i++) {
    auto frame_buffer = device->CreateFrameBuffer(
        render_pass_, {.attachments = {swap_chain->GetImageView(i)},
                       .extent = swap_chain_extent});
    frame_buffers_.push_back(frame_buffer);
  }

  pipeline_ = device->CreatePipeline(
      render_pass_,
      {.shader_set = {{chr::renderer::ShaderStage::kVertex, vertex_shader_},
                      {chr::renderer::ShaderStage::kFragment,
                       fragment_shader_}},
       .viewport = swap_chain_extent,
       .scissor = swap_chain_extent});

  command_pool_ = device->CreateCommandPool();

  command_buffers_.reserve(frame_buffers_.size());
  for (const auto& frame_buffer : frame_buffers_) {
    auto command_buffer = device->CreateCommandBuffer(command_pool_);
    command_buffer->Begin();
    command_buffer->BeginRenderPass(render_pass_, frame_buffer,
                                    {.render_area_offset = {0, 0},
                                     .render_area_extent = swap_chain_extent,
                                     .clear_colors = {{0, 0, 0, 1}}});
    command_buffer->BindPipeline(pipeline_);
    command_buffer->Draw({.vertex_count = 3, .first_vertex = 0});
    command_buffer->EndRenderPass();
    command_buffer->End();

    command_buffers_.push_back(command_buffer);
  }

  image_available_semaphores_.reserve(kMaxFramesInFlight);
  render_finished_semaphores_.reserve(kMaxFramesInFlight);
  in_flight_fences_.reserve(kMaxFramesInFlight);

  for (auto i = 0; i < kMaxFramesInFlight; i++) {
    image_available_semaphores_.push_back(device->CreateSemaphore());
    render_finished_semaphores_.push_back(device->CreateSemaphore());
    in_flight_fences_.push_back(device->CreateFence(true));
  }
}

auto ExampleApp::Destroy() -> void {
  CHR_ZONE_SCOPED();

  chr::log::Info("destroy");

  auto& platform = entt::locator<chr::platform::Platform>::value();
  const auto& device = platform.GetDevice();

  device->WaitIdle();

  platform.template Disconnect<chr::platform::KeyEvent>(this);
}

auto GetFenceStatus(const chr::renderer::Fence& fence) -> std::string {
  CHR_ZONE_SCOPED();

  switch (fence->GetStatus()) {
    case chr::renderer::FenceStatus::kSignaled:
      return "signaled";
      break;
    case chr::renderer::FenceStatus::kUnsignaled:
      return "unsignaled";
      break;
    case chr::renderer::FenceStatus::kUnkwown:
      return "unknown";
      break;
    default:
      break;
  }
  return {};
}

auto ExampleApp::Update() -> void {
  CHR_ZONE_SCOPED();

  const auto& platform = entt::locator<chr::platform::Platform>::value();

  platform.Update();

  const auto& device = platform.GetDevice();
  const auto& swap_chain = platform.GetSwapChain();

  const auto& in_flight_fence = in_flight_fences_.at(current_frame_);
  const auto& image_available_semaphore =
      image_available_semaphores_.at(current_frame_);
  const auto& render_finished_semaphore =
      render_finished_semaphores_.at(current_frame_);

  in_flight_fence->Wait();
  in_flight_fence->Reset();

  auto image_index =
      swap_chain->AcquireNextImage(image_available_semaphore, nullptr);

  const auto& command_buffer = command_buffers_.at(image_index);

  device->Submit({.wait_semaphores = {image_available_semaphore},
                  .signal_semaphores = {render_finished_semaphore},
                  .command_buffers = {command_buffer}},
                 in_flight_fence);

  device->Present({.wait_semaphores = {render_finished_semaphore},
                   .swap_chains = {swap_chain},
                   .image_index = image_index});

  current_frame_ = (current_frame_ + 1) % kMaxFramesInFlight;

  FrameMark
}

auto ExampleApp::OnKeyEvent(const chr::platform::KeyEvent& key_event) const
    -> void {
  CHR_ZONE_SCOPED();

  chr::log::Info("key: {}", (int)key_event.key);
}
