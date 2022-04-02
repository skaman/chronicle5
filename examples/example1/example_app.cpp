#include "example_app.h"

auto ExampleApp::init() -> void {
  chr::log::trace("init");
  platform_.template connect<chr::KeyEvent, &ExampleApp::onKeyEvent>(this);
}

auto ExampleApp::destroy() -> void {
  chr::log::trace("destroy"); 
  platform_.template disconnect<chr::KeyEvent>(this);
}

auto ExampleApp::update() -> void { platform_.update(); }

auto ExampleApp::onKeyEvent(const chr::KeyEvent &keyEvent) -> void {
  chr::log::info("key: {}", (int)keyEvent.key);
}
