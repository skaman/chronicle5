#pragma once

#include "vulkan_pch.h"

#include "instance.h"

namespace chr::renderer {

struct VulkanInstance : InstanceI {
  explicit VulkanInstance(const InstanceInfo &info);
  ~VulkanInstance();

  VulkanInstance(const VulkanInstance &) = delete;
  VulkanInstance &operator=(const VulkanInstance &) = delete;

  auto test() -> void;

  auto layers() const -> std::vector<VkLayerProperties>;
  auto extensions() const -> std::vector<VkExtensionProperties>;

  auto native_instance() const -> VkInstance { return instance_; }

private:
  auto setup_debug_messenger(DebugLevel level) -> void;

  auto validate_layers() const -> void;
  auto validate_extensions() const -> void;

  VkInstance instance_{VK_NULL_HANDLE};
  VkDebugUtilsMessengerEXT debug_messenger_{VK_NULL_HANDLE};

  std::vector<const char *> required_extensions_{};
  std::vector<const char *> required_layers_{};
};

} // namespace chr::renderer