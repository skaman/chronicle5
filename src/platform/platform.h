// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_PLATFORM_H_
#define CHR_PLATFORM_PLATFORM_H_

#include <entt/entt.hpp>

#include "events.h"

namespace chr::platform {

namespace internal {
struct GlfwPlatform;
}

template <typename T>
concept ConceptEvent = std::is_base_of_v<Event, T>;

struct Platform {
  template <ConceptEvent TEvent, auto Candidate, typename Type>
  auto Connect(Type &&value_or_instance) -> entt::connection {
    return app_dispatcher_.sink<TEvent>().template connect<Candidate>(
        std::forward<Type>(value_or_instance));
  }

  template <ConceptEvent TEvent, typename Type>
  auto Disconnect(Type *value_or_instance) -> void {
    return app_dispatcher_.sink<TEvent>().disconnect(value_or_instance);
  }

  auto Update() const -> void { app_dispatcher_.update(); }

 private:
  entt::dispatcher app_dispatcher_{};
  entt::dispatcher platform_dispatcher_{};

  friend struct chr::platform::internal::GlfwPlatform;
};

}  // namespace chr

#endif  // CHR_PLATFORM_PLATFORM_H_