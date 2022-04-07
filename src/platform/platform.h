#pragma once

#include "events.h"
#include <entt/entt.hpp>

namespace chr {

template <typename T>
concept ConceptEvent = std::is_base_of_v<Event, T>;

struct Platform {
  template <ConceptEvent TEvent, auto Candidate, typename Type>
  auto connect(Type &&value_or_instance) -> entt::connection {
    return app_dispatcher_.sink<TEvent>().template connect<Candidate>(
        std::forward<Type>(value_or_instance));
  }

  template <ConceptEvent TEvent, typename Type>
  auto disconnect(Type *value_or_instance) -> void {
    return app_dispatcher_.sink<TEvent>().disconnect(value_or_instance);
  }

  auto update() const -> void { app_dispatcher_.update(); }

private:
  entt::dispatcher app_dispatcher_{};
  entt::dispatcher platform_dispatcher_{};

  friend struct GlfwPlatform;
};

} // namespace chr