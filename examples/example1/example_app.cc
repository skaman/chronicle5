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
  storage.SetBasePath("F:/Progetti/TerrainGenerator");

  for (auto const& entry : storage.GetEntries("/")) {
    chr::log::Info("{} - {} - {} - {} - {}", entry.Name(), entry.IsDirectory(),
                   entry.Extension(), entry.HaveExtension(), entry.Size());
  }

  auto file = storage.GetFile("/README.md");
  file.Open();
  auto data = file.ReadAll();
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
