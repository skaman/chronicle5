// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "example_app.h"

CHR_INIT { chr::platform::RegisterApp<ExampleApp>(); }

auto ExampleApp::Init() -> void {
  chr::log::Info("init");
  GetPlatform()
      .template Connect<chr::platform::KeyEvent, &ExampleApp::OnKeyEvent>(this);

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

  auto fragment_shader =
      compiler.Compile(triangle_shader_frag_data, "triangle_shader.frag",
                       chr::renderer::ShaderStage::kFragment);

  auto vertex_shader =
      compiler.Compile(triangle_shader_vert_data, "triangle_shader.vert",
                       chr::renderer::ShaderStage::kVertex);
}

auto ExampleApp::Destroy() -> void {
  chr::log::Info("destroy");
  GetPlatform().template Disconnect<chr::platform::KeyEvent>(this);
}

auto ExampleApp::Update() -> void { GetPlatform().Update(); }

auto ExampleApp::OnKeyEvent(const chr::platform::KeyEvent& key_event) const
    -> void {
  chr::log::Info("key: {}", (int)key_event.key);
}
