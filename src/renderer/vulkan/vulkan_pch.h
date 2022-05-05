// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_VULKAN_VULKAN_PCH_H_
#define CHR_RENDERER_VULKAN_VULKAN_PCH_H_

#include <chronicle/common.h>

#include <stdexcept>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

#define CHR_ZONE_SCOPED_VULKAN() CHR_ZONE_SCOPED_COLOR(tracy::Color::Red)

#endif  // CHR_RENDERER_VULKAN_VULKAN_PCH_H_
