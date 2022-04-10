#pragma once

namespace chr::renderer {

enum class PlatformType { none, vulkan };

struct Platform {

  static auto type() -> PlatformType { return platform_; }
  static auto set_type(PlatformType platform) -> void { platform_ = platform; }

private:
  static PlatformType platform_;
};

} // namespace chr::renderer