#pragma once

#include <stdexcept>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

namespace chr::renderer {

struct VulkanException : public std::runtime_error {
  using std::runtime_error ::runtime_error;
};

} // namespace chr::renderer