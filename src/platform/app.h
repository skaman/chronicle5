#pragma once

#include <entt/entt.hpp>

#include "platform.h"

namespace chr {

struct Platform;

struct App {
  explicit App() {}
  virtual ~App() = default;

  virtual auto init() -> void = 0;
  virtual auto destroy() -> void = 0;
  virtual auto update() -> void = 0;

protected:
  Platform platform_;

  friend struct GlfwPlatform;
};

using namespace entt::literals;

template <typename T>
concept ConceptApp = std::is_base_of<App, T>::value;

template <ConceptApp T> void *register_app() {
  entt::meta<T>().type("app"_hs).template base<App>();
  return nullptr;
}

} // namespace chr