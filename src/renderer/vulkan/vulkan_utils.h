// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_UTILS_H_
#define CHR_RENDERER_VULKAN_VULKAN_UTILS_H_

#include "format.h"
#include "pch.h"
#include "vulkan_pch.h"

namespace chr::renderer::internal {

auto GetVulkanFormat(Format format) -> VkFormat;
auto GetLocalFormat(VkFormat format) -> Format;

}  // namespace chr::renderer::internal

#endif  // CHR_RENDERER_VULKAN_VULKAN_UTILS_H_