#pragma once

#include <entt/entt.hpp>

#include "platform.h"

namespace chr {

struct Platform;

struct App {
  explicit App() = default;
  virtual ~App() = default;

  virtual auto init() -> void = 0;
  virtual auto destroy() -> void = 0;
  virtual auto update() -> void = 0;

  [[nodiscard]] constexpr Platform &platform() { return platform_; }

private:
  Platform platform_;

  friend struct GlfwPlatform;
};

using entt::literals::operator""_hs;

template <typename T>
concept ConceptApp = std::is_base_of_v<App, T>;

template <ConceptApp T> void register_app() {
  entt::meta<T>().type("app"_hs).template base<App>();
}

#define CHR_CAT_IMPL(a, b) a##b
#define CHR_CAT(a, b) CHR_CAT_IMPL(a, b)

#define CHR_INIT                                                               \
  static void chr_auto_init_function_();                                       \
  namespace {                                                                  \
  struct chr__auto__init__ {                                                   \
    chr__auto__init__() { chr_auto_init_function_(); }                         \
  };                                                                           \
  }                                                                            \
  static const chr__auto__init__ CHR_CAT(auto_init__, __LINE__);               \
  static void chr_auto_init_function_()

} // namespace chr