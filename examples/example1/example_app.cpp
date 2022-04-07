#include "example_app.h"

auto ExampleApp::init() -> void {
  chr::log::info("init");
  platform().template connect<chr::KeyEvent, &ExampleApp::onKeyEvent>(this);
}

auto ExampleApp::destroy() -> void {
  chr::log::info("destroy"); 
  platform().template disconnect<chr::KeyEvent>(this);
}

auto ExampleApp::update() -> void { platform().update(); }

auto ExampleApp::onKeyEvent(const chr::KeyEvent &keyEvent) -> void {
  chr::log::info("key: {}", (int)keyEvent.key);
}
