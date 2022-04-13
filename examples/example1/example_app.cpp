#include "example_app.h"

CHR_INIT { chr::RegisterApp<ExampleApp>(); }

auto ExampleApp::Init() -> void {
  chr::log::Info("init");
  GetPlatform().template Connect<chr::KeyEvent, &ExampleApp::OnKeyEvent>(this);
}

auto ExampleApp::Destroy() -> void {
  chr::log::Info("destroy"); 
  GetPlatform().template Disconnect<chr::KeyEvent>(this);
}

auto ExampleApp::Update() -> void { GetPlatform().Update(); }

auto ExampleApp::OnKeyEvent(const chr::KeyEvent &key_event) const -> void {
  chr::log::Info("key: {}", (int)key_event.key);
}
