// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_PLATFORM_PLATFORM_H_
#define CHR_PLATFORM_PLATFORM_H_

#include <chronicle/renderer.h>

#include <entt/entt.hpp>

#include "events.h"

namespace chr::platform {

namespace internal {
struct GlfwPlatform;
}

template <typename T>
concept ConceptEvent = std::is_base_of_v<Event, T>;

struct Platform {
  explicit Platform(renderer::Instance instance, renderer::Surface surface,
                    renderer::Device device, renderer::SwapChain swapchain)
      : instance_{instance},
        surface_{surface},
        device_{device},
        swapchain_{swapchain} {}

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

  [[nodiscard]] auto GetInstance() const -> renderer::Instance {
    return instance_;
  }

  [[nodiscard]] auto GetSurface() const -> renderer::Surface {
    return surface_;
  }

  [[nodiscard]] auto GetDevice() const -> renderer::Device { return device_; }

  [[nodiscard]] auto GetSwapChain() const -> renderer::SwapChain {
    return swapchain_;
  }

 private:
  renderer::Instance instance_;
  renderer::Surface surface_;
  renderer::Device device_;
  renderer::SwapChain swapchain_;

  entt::dispatcher app_dispatcher_{};
  entt::dispatcher platform_dispatcher_{};

  friend struct chr::platform::internal::GlfwPlatform;
};

}  // namespace chr::platform

#endif  // CHR_PLATFORM_PLATFORM_H_