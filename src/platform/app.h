// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_APP_H_
#define CHR_PLATFORM_APP_H_

#include <chronicle/common.h>

#include "platform.h"

namespace chr::platform {

namespace internal {
struct GlfwPlatform;
}

struct Platform;

struct App {
  explicit App() = default;
  virtual ~App() = default;

  virtual auto Init() -> void = 0;
  virtual auto Destroy() -> void = 0;
  virtual auto Update() -> void = 0;
};

using entt::literals::operator""_hs;

template <typename T>
concept ConceptApp = std::is_base_of_v<App, T>;

template <ConceptApp T>
void RegisterApp() {
  entt::meta<T>().type("app"_hs).template base<App>();
}

#define CHR_CAT_IMPL(a, b) a##b
#define CHR_CAT(a, b) CHR_CAT_IMPL(a, b)

#define CHR_INIT                                                 \
  static void chr_auto_init_function_();                         \
  namespace {                                                    \
  struct chr__auto__init__ {                                     \
    chr__auto__init__() { chr_auto_init_function_(); }           \
  };                                                             \
  }                                                              \
  static const chr__auto__init__ CHR_CAT(auto_init__, __LINE__); \
  static void chr_auto_init_function_()

}  // namespace chr

#endif  // CHR_PLATFORM_APP_H_