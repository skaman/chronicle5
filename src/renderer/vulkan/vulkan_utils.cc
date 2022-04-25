// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "vulkan_utils.h"

#include "common.h"

namespace chr::renderer::internal {

auto GetLocalToVulkanFormatMap() -> std::unordered_map<Format, VkFormat> {
  return {
      // 8 bit
      {Format::kR4G4UNormPack8, VK_FORMAT_R4G4_UNORM_PACK8},
      {Format::kR8UNorm, VK_FORMAT_R8_UNORM},
      {Format::kR8SNorm, VK_FORMAT_R8_SNORM},
      {Format::kR8UScaled, VK_FORMAT_R8_USCALED},
      {Format::kR8SScaled, VK_FORMAT_R8_SSCALED},
      {Format::kR8UInt, VK_FORMAT_R8_UINT},
      {Format::kR8SInt, VK_FORMAT_R8_SINT},
      {Format::kR8SRGB, VK_FORMAT_R8_SRGB},

      // 16 bit
      {Format::kR4G4B4A4UNormPack16, VK_FORMAT_R4G4B4A4_UNORM_PACK16},
      {Format::kB4G4R4A4UNormPack16, VK_FORMAT_B4G4R4A4_UNORM_PACK16},
      {Format::kR5G6B5UnormPack16, VK_FORMAT_R5G6B5_UNORM_PACK16},
      {Format::kB5G6R5UnormPack16, VK_FORMAT_B5G6R5_UNORM_PACK16},
      {Format::kR5G5B5A1UNormPack16, VK_FORMAT_R5G5B5A1_UNORM_PACK16},
      {Format::kB5G5R5A1UNormPack16, VK_FORMAT_B5G5R5A1_UNORM_PACK16},
      {Format::kA1R5G5B5UNormPack16, VK_FORMAT_A1R5G5B5_UNORM_PACK16},
      {Format::kR8G8UNorm, VK_FORMAT_R8G8_UNORM},
      {Format::kR8G8SNorm, VK_FORMAT_R8G8_SNORM},
      {Format::kR8G8UScaled, VK_FORMAT_R8G8_USCALED},
      {Format::kR8G8SScaled, VK_FORMAT_R8G8_SSCALED},
      {Format::kR8G8UInt, VK_FORMAT_R8G8_UINT},
      {Format::kR8G8SInt, VK_FORMAT_R8G8_SINT},
      {Format::kR8G8sSRGB, VK_FORMAT_R8G8_SRGB},
      {Format::kR16UNorm, VK_FORMAT_R16_UNORM},
      {Format::kR16SNorm, VK_FORMAT_R16_SNORM},
      {Format::kR16UScaled, VK_FORMAT_R16_USCALED},
      {Format::kR16SScaled, VK_FORMAT_R16_SSCALED},
      {Format::kR16UInt, VK_FORMAT_R16_UINT},
      {Format::kR16SInt, VK_FORMAT_R16_SINT},
      {Format::kR16SFloat, VK_FORMAT_R16_SFLOAT},
      {Format::kR10X6UNormPack16, VK_FORMAT_R10X6_UNORM_PACK16},
      {Format::kR12X4UNormPack16, VK_FORMAT_R12X4_UNORM_PACK16},
      {Format::kA4R4G4B4UNormPack16, VK_FORMAT_A4R4G4B4_UNORM_PACK16},
      {Format::kA4B4G4R4UNormPack16, VK_FORMAT_A4B4G4R4_UNORM_PACK16},

      // 24 bit
      {Format::kR8G8B8UNorm, VK_FORMAT_R8G8B8_UNORM},
      {Format::kR8G8B8SNorm, VK_FORMAT_R8G8B8_SNORM},
      {Format::kR8G8B8UScaled, VK_FORMAT_R8G8B8_USCALED},
      {Format::kR8G8B8SScaled, VK_FORMAT_R8G8B8_SSCALED},
      {Format::kR8G8B8UInt, VK_FORMAT_R8G8B8_UINT},
      {Format::kR8G8B8SInt, VK_FORMAT_R8G8B8_SINT},
      {Format::kR8G8B8SRGB, VK_FORMAT_R8G8B8_SRGB},
      {Format::kB8G8R8UNorm, VK_FORMAT_B8G8R8_UNORM},
      {Format::kB8G8R8SNorm, VK_FORMAT_B8G8R8_SNORM},
      {Format::kB8G8R8UScaled, VK_FORMAT_B8G8R8_USCALED},
      {Format::kB8G8R8SScaled, VK_FORMAT_B8G8R8_SSCALED},
      {Format::kB8G8R8UInt, VK_FORMAT_B8G8R8_UINT},
      {Format::kB8G8R8SInt, VK_FORMAT_B8G8R8_SINT},
      {Format::kB8G8R8SRGB, VK_FORMAT_B8G8R8_SRGB},

      // 32 bit
      {Format::kR8G8B8A8UNorm, VK_FORMAT_R8G8B8A8_UNORM},
      {Format::kR8G8B8A8SNorm, VK_FORMAT_R8G8B8A8_SNORM},
      {Format::kR8G8B8A8UScaled, VK_FORMAT_R8G8B8A8_USCALED},
      {Format::kR8G8B8A8SScaled, VK_FORMAT_R8G8B8A8_SSCALED},
      {Format::kR8G8B8A8UInt, VK_FORMAT_R8G8B8A8_UINT},
      {Format::kR8G8B8A8SInt, VK_FORMAT_R8G8B8A8_SINT},
      {Format::kR8G8B8A8SRGB, VK_FORMAT_R8G8B8A8_SRGB},
      {Format::kB8G8R8A8UNorm, VK_FORMAT_B8G8R8A8_UNORM},
      {Format::kB8G8R8A8SNorm, VK_FORMAT_B8G8R8A8_SNORM},
      {Format::kB8G8R8A8UScaled, VK_FORMAT_B8G8R8A8_USCALED},
      {Format::kB8G8R8A8SScaled, VK_FORMAT_B8G8R8A8_SSCALED},
      {Format::kB8G8R8A8UInt, VK_FORMAT_B8G8R8A8_UINT},
      {Format::kB8G8R8A8SInt, VK_FORMAT_B8G8R8A8_SINT},
      {Format::kB8G8R8A8SRGB, VK_FORMAT_B8G8R8A8_SRGB},
      {Format::kA8B8G8R8UNormPack32, VK_FORMAT_A8B8G8R8_UNORM_PACK32},
      {Format::kA8B8G8R8SNormPack32, VK_FORMAT_A8B8G8R8_SNORM_PACK32},
      {Format::kA8B8G8R8UScaledPack32, VK_FORMAT_A8B8G8R8_USCALED_PACK32},
      {Format::kA8B8G8R8SScaledPack32, VK_FORMAT_A8B8G8R8_SSCALED_PACK32},
      {Format::kA8B8G8R8UIntPack32, VK_FORMAT_A8B8G8R8_UINT_PACK32},
      {Format::kA8B8G8R8SIntPack32, VK_FORMAT_A8B8G8R8_SINT_PACK32},
      {Format::kA8B8G8R8SRGBPack32, VK_FORMAT_A8B8G8R8_SRGB_PACK32},
      {Format::kA2R10G10B10UNormPack32, VK_FORMAT_A2R10G10B10_UNORM_PACK32},
      {Format::kA2R10G10B10SNormPack32, VK_FORMAT_A2R10G10B10_SNORM_PACK32},
      {Format::kA2R10G10B10UScaledPack32, VK_FORMAT_A2R10G10B10_USCALED_PACK32},
      {Format::kA2R10G10B10SScaledPack32, VK_FORMAT_A2R10G10B10_SSCALED_PACK32},
      {Format::kA2R10G10B10UIntPack32, VK_FORMAT_A2R10G10B10_UINT_PACK32},
      {Format::kA2R10G10B10SIntPack32, VK_FORMAT_A2R10G10B10_SINT_PACK32},
      {Format::kA2B10G10R10UNormPack32, VK_FORMAT_A2B10G10R10_UNORM_PACK32},
      {Format::kA2B10G10R10SNormPack32, VK_FORMAT_A2B10G10R10_SNORM_PACK32},
      {Format::kA2B10G10R10UScaledPack32, VK_FORMAT_A2B10G10R10_USCALED_PACK32},
      {Format::kA2B10G10R10SScaledPack32, VK_FORMAT_A2B10G10R10_SSCALED_PACK32},
      {Format::kA2B10G10R10UIntPack32, VK_FORMAT_A2B10G10R10_UINT_PACK32},
      {Format::kA2B10G10R10SIntPack32, VK_FORMAT_A2B10G10R10_SINT_PACK32},
      {Format::kR16G16UNorm, VK_FORMAT_R16G16_UNORM},
      {Format::kR16G16SNorm, VK_FORMAT_R16G16_SNORM},
      {Format::kR16G16UScaled, VK_FORMAT_R16G16_USCALED},
      {Format::kR16G16SScaled, VK_FORMAT_R16G16_SSCALED},
      {Format::kR16G16UInt, VK_FORMAT_R16G16_UINT},
      {Format::kR16G16SInt, VK_FORMAT_R16G16_SINT},
      {Format::kR16G16SFloat, VK_FORMAT_R16G16_SFLOAT},
      {Format::kR32UInt, VK_FORMAT_R32_UINT},
      {Format::kR32SInt, VK_FORMAT_R32_SINT},
      {Format::kR32SFloat, VK_FORMAT_R32_SFLOAT},
      {Format::kB10G11R11UFloatPack32, VK_FORMAT_B10G11R11_UFLOAT_PACK32},
      {Format::kE5B9G9R9UFloatPack32, VK_FORMAT_E5B9G9R9_UFLOAT_PACK32},
      {Format::kR10X6G10X6UNorm2Pack16, VK_FORMAT_R10X6G10X6_UNORM_2PACK16},
      {Format::kR12X4G12X4UNorm2Pack16, VK_FORMAT_R12X4G12X4_UNORM_2PACK16},

      // 48 bit
      {Format::kR16G16B16UNorm, VK_FORMAT_R16G16B16_UNORM},
      {Format::kR16G16B16SNorm, VK_FORMAT_R16G16B16_SNORM},
      {Format::kR16G16B16UScaled, VK_FORMAT_R16G16B16_USCALED},
      {Format::kR16G16B16SScaled, VK_FORMAT_R16G16B16_SSCALED},
      {Format::kR16G16B16UInt, VK_FORMAT_R16G16B16_UINT},
      {Format::kR16G16B16SInt, VK_FORMAT_R16G16B16_SINT},
      {Format::kR16G16B16SFloat, VK_FORMAT_R16G16B16_SFLOAT},

      // 64 bit
      {Format::kR16G16B16A16UNorm, VK_FORMAT_R16G16B16A16_UNORM},
      {Format::kR16G16B16A16SNorm, VK_FORMAT_R16G16B16A16_SNORM},
      {Format::kR16G16B16A16UScaled, VK_FORMAT_R16G16B16A16_USCALED},
      {Format::kR16G16B16A16SScaled, VK_FORMAT_R16G16B16A16_SSCALED},
      {Format::kR16G16B16A16UInt, VK_FORMAT_R16G16B16A16_UINT},
      {Format::kR16G16B16A16SInt, VK_FORMAT_R16G16B16A16_SINT},
      {Format::kR16G16B16A16SFloat, VK_FORMAT_R16G16B16A16_SFLOAT},
      {Format::kR32G32UInt, VK_FORMAT_R32G32_UINT},
      {Format::kR32G32SInt, VK_FORMAT_R32G32_SINT},
      {Format::kR32G32SFloat, VK_FORMAT_R32G32_SFLOAT},
      {Format::kR64UInt, VK_FORMAT_R64_UINT},
      {Format::kR64SInt, VK_FORMAT_R64_SINT},
      {Format::kR64SFloat, VK_FORMAT_R64_SFLOAT},

      // 96 bit
      {Format::kR32G32B32UInt, VK_FORMAT_R32G32B32_UINT},
      {Format::kR32G32B32SInt, VK_FORMAT_R32G32B32_SINT},
      {Format::kR32G32B32SFloat, VK_FORMAT_R32G32B32_SFLOAT},

      // 128 bit
      {Format::kR32G32B32A32UInt, VK_FORMAT_R32G32B32A32_UINT},
      {Format::kR32G32B32A32SInt, VK_FORMAT_R32G32B32A32_SINT},
      {Format::kR32G32B32A32SFloat, VK_FORMAT_R32G32B32A32_SFLOAT},
      {Format::kR64G64UInt, VK_FORMAT_R64G64_UINT},
      {Format::kR64G64SInt, VK_FORMAT_R64G64_SINT},
      {Format::kR64G64SFloat, VK_FORMAT_R64G64_SFLOAT},

      // 192 bit
      {Format::kR64G64B64UInt, VK_FORMAT_R64G64B64_UINT},
      {Format::kR64G64B64SInt, VK_FORMAT_R64G64B64_SINT},
      {Format::kR64G64B64SFloat, VK_FORMAT_R64G64B64_SFLOAT},

      // 256 bit
      {Format::kR64G64B64A64UInt, VK_FORMAT_R64G64B64A64_UINT},
      {Format::kR64G64B64A64SInt, VK_FORMAT_R64G64B64A64_SINT},
      {Format::kR64G64B64A64SFloat, VK_FORMAT_R64G64B64A64_SFLOAT},
  };
}

auto GetVulkanToLocalFormatMap() -> std::unordered_map<VkFormat, Format> {
  auto local_to_vulkan_map = GetLocalToVulkanFormatMap();
  return utils::InverseMap<Format, VkFormat>(local_to_vulkan_map);
}

static const std::unordered_map<Format, VkFormat> kLocalToVulkanFormatMap =
    GetLocalToVulkanFormatMap();

static const std::unordered_map<VkFormat, Format> kVulkanToLocalFormatMap =
    GetVulkanToLocalFormatMap();

auto GetVulkanFormat(Format format) -> VkFormat {
  if (!kLocalToVulkanFormatMap.contains(format)) {
    debug::Assert(false, "Unsupported format.");
    return VK_FORMAT_UNDEFINED;
  }

  return kLocalToVulkanFormatMap.at(format);
}

auto GetLocalFormat(VkFormat format) -> Format {
  if (!kVulkanToLocalFormatMap.contains(format)) {
    debug::Assert(false, "Unsupported format.");
    return Format::kUndefined;
  }

  return kVulkanToLocalFormatMap.at(format);
}

auto GetShaderStageFlagBits(ShaderStage stage) -> VkShaderStageFlagBits {
  switch (stage) {
    case ShaderStage::kVertex:
      return VK_SHADER_STAGE_VERTEX_BIT;
    case ShaderStage::kFragment:
      return VK_SHADER_STAGE_FRAGMENT_BIT;
    case ShaderStage::kCompute:
      return VK_SHADER_STAGE_COMPUTE_BIT;
    case ShaderStage::kAllGraphics:
      return VK_SHADER_STAGE_ALL_GRAPHICS;
    case ShaderStage::kAll:
      return VK_SHADER_STAGE_ALL;
    default:
      break;
  }

  debug::Assert(false, "Unsupported shader stage");

  return static_cast<VkShaderStageFlagBits>(0);
}

}  // namespace chr::renderer::internal