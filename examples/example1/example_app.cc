// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "example_app.h"

CHR_INIT { chr::platform::RegisterApp<ExampleApp>(); }

auto ExampleApp::Init() -> void {
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

  auto& instance = platform.GetInstance();
  const auto& device = platform.GetDevice();
  const auto& swap_chain = platform.GetSwapChain();

  auto swap_chain_extent = swap_chain.GetExtent();
  auto swap_chain_format = swap_chain.GetFormat();

  auto fragment_shader =
      instance.CreateShader(device, fragment_shader_compiled.data);
  auto vertex_shader =
      instance.CreateShader(device, vertex_shader_compiled.data);

  auto render_pass =
      instance.CreateRenderPass(device, {.format = swap_chain_format});

  auto swap_chain_image_view_count = swap_chain.GetImageViewCount();
  std::vector<chr::renderer::FrameBuffer> swap_chain_frame_buffers{};
  swap_chain_frame_buffers.reserve(swap_chain_image_view_count);
  for (auto i = 0; i < swap_chain_image_view_count; i++) {
    auto frame_buffer =
        instance.CreateFrameBuffer(device, render_pass,
                                   {.attachments = {swap_chain.GetImageView(i)},
                                    .extent = swap_chain_extent});
  }

  auto pipeline = instance.CreatePipeline(
      device, render_pass,
      {.shader_set = {{chr::renderer::ShaderStage::kVertex, vertex_shader},
                      {chr::renderer::ShaderStage::kFragment, fragment_shader}},
       .viewport = swap_chain_extent,
       .scissor = swap_chain_extent});
}

auto ExampleApp::Destroy() -> void {
  chr::log::Info("destroy");
  auto& platform = entt::locator<chr::platform::Platform>::value();

  platform.template Disconnect<chr::platform::KeyEvent>(this);
}

auto ExampleApp::Update() -> void {
  const auto& platform = entt::locator<chr::platform::Platform>::value();

  platform.Update();
}

auto ExampleApp::OnKeyEvent(const chr::platform::KeyEvent& key_event) const
    -> void {
  chr::log::Info("key: {}", (int)key_event.key);
}
