// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_INSTANCE_H_
#define CHR_RENDERER_VULKAN_VULKAN_INSTANCE_H_

#include "instance.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

struct VulkanInstance : InstanceI {
  explicit VulkanInstance(const InstanceInfo &info);
  ~VulkanInstance();

  VulkanInstance(const VulkanInstance &) = delete;
  VulkanInstance &operator=(const VulkanInstance &) = delete;

  auto test() -> void;

  auto GetLayers() const -> std::vector<VkLayerProperties>;
  auto GetExtensions() const -> std::vector<VkExtensionProperties>;

  auto GetNativeInstance() const -> VkInstance { return instance_; }

 private:
  auto SetupDebugMessenger(DebugLevel level) -> void;

  auto ValidateLayers() const -> void;
  auto ValidateExtensions() const -> void;

  VkInstance instance_{VK_NULL_HANDLE};
  VkDebugUtilsMessengerEXT debug_messenger_{VK_NULL_HANDLE};

  std::vector<const char *> required_extensions_{};
  std::vector<const char *> required_layers_{};
};

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_INSTANCE_H_