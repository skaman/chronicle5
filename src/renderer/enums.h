// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_ENUMS_H_
#define CHR_RENDERER_ENUMS_H_

#include "common.h"

namespace chr::renderer {

//! @brief Debug level for renderer driver.
enum class DebugLevel {
  kNone,     //!< Log nothing.
  kVerbose,  //!< Verbose logging.
  kWarning,  //!< Log only warning and errors.
  kError     //!< Log only errors.
};

//! @brief Renderer backend type.
enum class BackendType {
  kVulkan  //!< Vulkan renderer.
};

//! @brief Shader stages for commands and structures.
enum class ShaderStage {
  kVertex,    //!< Vertex stage.
  kFragment,  //!< Fragment stage.
  kCompute,   //!< Compute stage.

  kAllGraphics,  //!< All graphics stages.
  kAll           //!< All stages.
};

//! @brief Image formats that can be passed to, and may be returned from
//!        renderer commands.
enum class Format {
  //! @brief Format is not specified,
  kUndefined,

  // 8 bit - Block size 1 byte

  //! @brief 2 components, 8-bit packed unsigned normalized format that has a
  //!        4-bit R component in bits 4..7, and a 4-bit G component in bits
  //!        0..3.
  kR4G4UNormPack8,

  //! @brief 1 component, 8-bit unsigned normalized format that has a single
  //!        8-bit R component.
  kR8UNorm,

  //! @brief 1 component, 8-bit signed normalized format that has a single 8-bit
  //!        R component.
  kR8SNorm,

  //! @brief 1 component, 8-bit unsigned scaled integer format that has a single
  //!        8-bit R component.
  kR8UScaled,

  //! @brief 1 component, 8-bit signed scaled integer format that has a single
  //!        8-bit R component.
  kR8SScaled,

  //! @brief 1 component, 8-bit unsigned integer format that has a single 8-bit
  //!        R component.
  kR8UInt,

  //! @brief 1 component, 8-bit signed integer format that has a single 8-bit R
  //!        component.
  kR8SInt,

  //! @brief 1 component, 8-bit unsigned normalized format that has a single
  //!        8-bit R component stored with sRGB nonlinear encoding.
  kR8SRGB,

  // 16 bit - Block size 2 byte

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        4-bit R component in bits 12..15, a 4-bit G component in
  //!        bits 8..11, a 4-bit B component in bits 4..7, and a 4-bit A
  //!        component in bits 0..3.
  kR4G4B4A4UNormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        4-bit B component in bits 12..15, a 4-bit G component in
  //!        bits 8..11, a 4-bit R component in bits 4..7, and a 4-bit A
  //!        component in bits 0..3.
  kB4G4R4A4UNormPack16,

  //! @brief 3 components, 16-bit packed unsigned normalized format that has a
  //!        5-bit R component in bits 11..15, a 6-bit G component in
  //!        bits 5..10, and a 5-bit B component in bits 0..4.
  kR5G6B5UnormPack16,

  //! @brief 3 components, 16-bit packed unsigned normalized format that has a
  //!        5-bit B component in bits 11..15, a 6-bit G component in
  //!        bits 5..10, and a 5-bit R component in bits 0..4.
  kB5G6R5UnormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        5-bit R component in bits 11..15, a 5-bit G component in
  //!        bits 6..10, a 5-bit B component in bits 1..5, and a 1-bit A
  //!        component in bit 0.
  kR5G5B5A1UNormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        5-bit B component in bits 11..15, a 5-bit G component in
  //!        bits 6..10, a 5-bit R component in bits 1..5, and a 1-bit A
  //!        component in bit 0.
  kB5G5R5A1UNormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        1-bit A component in bit 15, a 5-bit R component in bits 10..14, a
  //!        5-bit G component in bits 5..9, and a 5-bit B component in bits
  //!        0..4.
  kA1R5G5B5UNormPack16,

  //! @brief 2 components, 16-bit unsigned normalized format that has an 8-bit R
  //!        component in byte 0, and an 8-bit G component in byte 1.
  kR8G8UNorm,

  //! @brief 2 components, 16-bit signed normalized format that has an 8-bit R
  //!        component in byte 0, and an 8-bit G component in byte 1.
  kR8G8SNorm,

  //! @brief 2 components, 16-bit unsigned scaled integer format that has an
  //!        8-bit R component in byte 0, and an 8-bit G component in byte 1.
  kR8G8UScaled,

  //! @brief 2 components, 16-bit signed scaled integer format that has an 8-bit
  //!        R component in byte 0, and an 8-bit G component in byte 1.
  kR8G8SScaled,

  //! @brief 2 components, 16-bit unsigned integer format that has an 8-bit R
  //!        component in byte 0, and an 8-bit G component in byte 1.
  kR8G8UInt,

  //! @brief 2 components, 16-bit signed integer format that has an 8-bit R
  //!        component in byte 0, and an 8-bit G component in byte 1.
  kR8G8SInt,

  //! @brief 2 components, 16-bit unsigned normalized format that has an 8-bit R
  //!        component stored with sRGB nonlinear encoding in byte 0, and an
  //!        8-bit G component stored with sRGB nonlinear encoding in byte 1.
  kR8G8sSRGB,

  //! @brief 1 component, 16-bit unsigned normalized format that has a single
  //!        16-bit R component.
  kR16UNorm,

  //! @brief 1 component, 16-bit signed normalized format that has a single
  //!        16-bit R component.
  kR16SNorm,

  //! @brief 1 component, 16-bit unsigned scaled integer format that has a
  //! single 16-bit R component.
  kR16UScaled,

  //! @brief 1 component, 16-bit signed scaled integer format that has a single
  //!        16-bit R component.
  kR16SScaled,

  //! @brief 1 component, 16-bit unsigned integer format that has a single
  //!        16-bit R component.
  kR16UInt,

  //! @brief 1 component, 16-bit signed integer format that has a single 16-bit
  //!        R component.
  kR16SInt,

  //! @brief 1 component, 16-bit signed floating-point format that has a single
  //!        16-bit R component.
  kR16SFloat,

  //! @brief 1 component, 16-bit unsigned normalized format that has a single
  //!        10-bit R component in the top 10 bits of a 16-bit word, with the
  //!        bottom 6 bits unused.
  kR10X6UNormPack16,

  //! @brief 1 component, 16-bit unsigned normalized format that has a single
  //!        12-bit R component in the top 12 bits of a 16-bit word, with the
  //!        bottom 4 bits unused.
  kR12X4UNormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        4-bit A component in bits 12..15, a 4-bit R component in
  //!        bits 8..11, a 4-bit G component in bits 4..7, and a 4-bit B
  //!        component in bits 0..3.
  kA4R4G4B4UNormPack16,

  //! @brief 4 components, 16-bit packed unsigned normalized format that has a
  //!        4-bit A component in bits 12..15, a 4-bit B component in
  //!        bits 8..11, a 4-bit G component in bits 4..7, and a 4-bit R
  //!        component in bits 0..3.
  kA4B4G4R4UNormPack16,

  // 24 bit - Block size 3 byte

  //! @brief 3 components, 24-bit unsigned normalized format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8UNorm,

  //! @brief 3 components, 24-bit signed normalized format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8SNorm,

  //! @brief 3 components, 24-bit unsigned scaled format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8UScaled,

  //! @brief 3 components, 24-bit signed scaled format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8SScaled,

  //! @brief 3 components, 24-bit unsigned integer format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8UInt,

  //! @brief 3 components, 24-bit signed integer format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit B
  //!        component in byte 2.
  kR8G8B8SInt,

  //! @brief 3 components, 24-bit unsigned normalized format that has an 8-bit R
  //!        component stored with sRGB nonlinear encoding in byte 0, an 8-bit G
  //!        component stored with sRGB nonlinear encoding in byte 1, and an
  //!        8-bit B component stored with sRGB nonlinear encoding in byte 2.
  kR8G8B8SRGB,

  //! @brief 3 components, 24-bit unsigned normalized format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8UNorm,

  //! @brief 3 components, 24-bit signed normalized format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8SNorm,

  //! @brief 3 components, 24-bit unsigned scaled format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8UScaled,

  //! @brief 3 components, 24-bit signed scaled format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8SScaled,

  //! @brief 3 components, 24-bit unsigned integer format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8UInt,

  //! @brief 3 components, 24-bit signed integer format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, and an 8-bit R
  //!        component in byte 2.
  kB8G8R8SInt,

  //! @brief 3 components, 24-bit unsigned normalized format that has an 8-bit B
  //!        component stored with sRGB nonlinear encoding in byte 0, an 8-bit G
  //!        component stored with sRGB nonlinear encoding in byte 1, and an
  //!        8-bit R component stored with sRGB nonlinear encoding in byte 2.
  kB8G8R8SRGB,

  // 32 bit - Block size 4 byte

  //! @brief 4 component, 32-bit unsigned normalized format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8UNorm,

  //! @brief 4 components, 32-bit signed normalized format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8SNorm,

  //! @brief 4 components, 32-bit unsigned scaled format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8UScaled,

  //! @brief 4 components, 32-bit signed scaled format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8SScaled,

  //! @brief 4 components, 32-bit unsigned integer format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8UInt,

  //! @brief 4 components, 32-bit signed integer format that has an 8-bit R
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit B
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kR8G8B8A8SInt,

  //! @brief 4 components, 32-bit unsigned normalized format that has an 8-bit R
  //!        component stored with sRGB nonlinear encoding in byte 0, an 8-bit G
  //!        component stored with sRGB nonlinear encoding in byte 1, an 8-bit B
  //!        component stored with sRGB nonlinear encoding in byte 2, and an
  //!        8-bit A component in byte 3.
  kR8G8B8A8SRGB,

  //! @brief 4 components, 32-bit unsigned normalized format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8UNorm,

  //! @brief 4 components, 32-bit signed normalized format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8SNorm,

  //! @brief 4 components, 32-bit unsigned scaled format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8UScaled,

  //! @brief 4 components, 32-bit signed scaled format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8SScaled,

  //! @brief 4 components, 32-bit unsigned integer format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8UInt,

  //! @brief 4 components, 32-bit signed integer format that has an 8-bit B
  //!        component in byte 0, an 8-bit G component in byte 1, an 8-bit R
  //!        component in byte 2, and an 8-bit A component in byte 3.
  kB8G8R8A8SInt,

  //! @brief 4 components, 32-bit unsigned normalized format that has an 8-bit B
  //!        component stored with sRGB nonlinear encoding in byte 0, an 8-bit G
  //!        component stored with sRGB nonlinear encoding in byte 1, an 8-bit R
  //!        component stored with sRGB nonlinear encoding in byte 2, and an
  //!        8-bit A component in byte 3.
  kB8G8R8A8SRGB,

  //! @brief 4 components, 32-bit packed unsigned normalized format that has
  //!        an 8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8UNormPack32,

  //! @brief 4 components, 32-bit packed signed normalized format that has an
  //!        8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8SNormPack32,

  //! @brief 4 components, 32-bit packed unsigned scaled integer format that
  //!        has an 8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8UScaledPack32,

  //! @brief 4 components, 32-bit packed signed scaled integer format that has
  //!        an 8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8SScaledPack32,

  //! @brief 4 components, 32-bit packed unsigned integer format that has an
  //!        8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8UIntPack32,

  //! @brief 4 components, 32-bit packed signed integer format that has an
  //!        8-bit A component in bits 24..31, an 8-bit B component in
  //!        bits 16..23, an 8-bit G component in bits 8..15, and an 8-bit R
  //!        component in bits 0..7.
  kA8B8G8R8SIntPack32,

  //! @brief 4 components, 32-bit packed unsigned normalized format that has
  //!        an 8-bit A component in bits 24..31, an 8-bit B component stored
  //!        with sRGB nonlinear encoding in bits 16..23, an 8-bit G component
  //!        stored with sRGB nonlinear encoding in bits 8..15, and an 8-bit R
  //!        component stored with sRGB nonlinear encoding in bits 0..7.
  kA8B8G8R8SRGBPack32,

  //! @brief 4 components, 32-bit packed unsigned normalized format that has a
  //!        2-bit A component in bits 30..31, a 10-bit R component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B
  //!        component in bits 0..9.
  kA2R10G10B10UNormPack32,

  //! @brief 4 components, 32-bit packed signed normalized format that has a
  //!        2-bit A component in bits 30..31, a 10-bit R component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B
  //!        component in bits 0..9.
  kA2R10G10B10SNormPack32,

  //! @brief 4 components, 32-bit packed unsigned scaled integer format that has
  //!        a 2-bit A component in bits 30..31, a 10-bit R component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B
  //!        component in bits 0..9.
  kA2R10G10B10UScaledPack32,

  //! @brief 4 components, 32-bit packed signed scaled integer format that has a
  //!        2-bit A component in bits 30..31, a 10-bit R component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit B
  //!        component in bits 0..9.
  kA2R10G10B10SScaledPack32,

  //! @brief 4 components, 32-bit packed unsigned integer format that has a
  //! 2-bit
  //!        A component in bits 30..31, a 10-bit R component in bits 20..29, a
  //!        10-bit G component in bits 10..19, and a 10-bit B component in bits
  //!        0..9.
  kA2R10G10B10UIntPack32,

  //! @brief 4 components, 32-bit packed signed integer format that has a 2-bit
  //! A
  //!        component in bits 30..31, a 10-bit R component in bits 20..29, a
  //!        10-bit G component in bits 10..19, and a 10-bit B component in bits
  //!        0..9.
  kA2R10G10B10SIntPack32,

  //! @brief 4 components, 32-bit packed unsigned normalized format that has a
  //!        2-bit A component in bits 30..31, a 10-bit B component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R
  //!        component in bits 0..9.
  kA2B10G10R10UNormPack32,

  //! @brief 4 components, 32-bit packed signed normalized format that has a
  //!        2-bit A component in bits 30..31, a 10-bit B component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R
  //!        component in bits 0..9.
  kA2B10G10R10SNormPack32,

  //! @brief 4 components, 32-bit packed unsigned scaled integer format that has
  //!        a 2-bit A component in bits 30..31, a 10-bit B component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R
  //!        component in bits 0..9.
  kA2B10G10R10UScaledPack32,

  //! @brief 4 components, 32-bit packed signed scaled integer format that has a
  //!        2-bit A component in bits 30..31, a 10-bit B component in
  //!        bits 20..29, a 10-bit G component in bits 10..19, and a 10-bit R
  //!        component in bits 0..9.
  kA2B10G10R10SScaledPack32,

  //! @brief 4 components, 32-bit packed unsigned integer format that has a
  //! 2-bit
  //!        A component in bits 30..31, a 10-bit B component in bits 20..29, a
  //!        10-bit G component in bits 10..19, and a 10-bit R component in bits
  //!        0..9.
  kA2B10G10R10UIntPack32,

  //! @brief 4 components, 32-bit packed signed integer format that has a 2-bit
  //!        A component in bits 30..31, a 10-bit B component in bits 20..29, a
  //!        10-bit G component in bits 10..19, and a 10-bit R component in bits
  //!        0..9.
  kA2B10G10R10SIntPack32,

  //! @brief 2 components, 32-bit unsigned normalized format that has a 16-bit R
  //!        component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16UNorm,

  //! @brief 2 components, 32-bit signed normalized format that has a 16-bit R
  //!        component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16SNorm,

  //! @brief 2 components, 32-bit unsigned scaled integer format that has a
  //!        16-bit R component in bytes 0..1, and a 16-bit G component in
  //!        bytes 2..3.
  kR16G16UScaled,

  //! @brief 2 components, 32-bit signed scaled integer format that has a 16-bit
  //!        R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16SScaled,

  //! @brief 2 components, 32-bit unsigned integer format that has a 16-bit R
  //!        component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16UInt,

  //! @brief 2 components, 32-bit signed integer format that has a 16-bit R
  //!        component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16SInt,

  //! @brief 2 components, 32-bit signed floating-point format that has a 16-bit
  //!        R component in bytes 0..1, and a 16-bit G component in bytes 2..3.
  kR16G16SFloat,

  //! @brief 1 components, 32-bit unsigned integer format that has a single
  //!        32-bit R component.
  kR32UInt,

  //! @brief 1 component, 32-bit signed integer format that has a single 32-bit
  //!        R component.
  kR32SInt,

  //! @brief 1 component, 32-bit signed floating-point format that has a single
  //!        32-bit R component.
  kR32SFloat,

  //! @brief 3 components, 32-bit packed unsigned floating-point format that has
  //!        a 10-bit B component in bits 22..31, an 11-bit G component in
  //!        bits 11..21, an 11-bit R component in bits 0..10.
  kB10G11R11UFloatPack32,

  //! @brief 3 components, 32-bit packed unsigned floating-point format that has
  //!        a 5-bit shared exponent in bits 27..31, a 9-bit B component
  //!        mantissa in bits 18..26, a 9-bit G component mantissa in
  //!        bits 9..17, and a 9-bit R component mantissa in bits 0..8.
  kE5B9G9R9UFloatPack32,

  //! @brief 2 components, 32-bit unsigned normalized format that has a 10-bit R
  //!        component in the top 10 bits of the word in bytes 0..1, and a
  //!        10-bit G component in the top 10 bits of the word in bytes 2..3,
  //!        with the bottom 6 bits of each word unused.
  kR10X6G10X6UNorm2Pack16,

  //! @brief 2 components, 32-bit unsigned normalized format that has a 12-bit R
  //!        component in the top 12 bits of the word in bytes 0..1, and a
  //!        12-bit G component in the top 12 bits of the word in bytes 2..3,
  //!        with the bottom 4 bits of each word unused.
  kR12X4G12X4UNorm2Pack16,

  // 48 bit - Block size 6 byte

  //! @brief 3 components, 48-bit unsigned normalized format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, and a
  //!        16-bit B component in bytes 4..5.
  kR16G16B16UNorm,

  //! @brief 3 components, 48-bit signed normalized format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, and a
  //!        16-bit B component in bytes 4..5.
  kR16G16B16SNorm,

  //! @brief 3 components, 48-bit unsigned scaled integer format that has a
  //!        16-bit R component in bytes 0..1, a 16-bit G component in
  //!        bytes 2..3, and a 16-bit B component in bytes 4..5.
  kR16G16B16UScaled,

  //! @brief 3 components, 48-bit signed scaled integer format that has a 16-bit
  //!        R component in bytes 0..1, a 16-bit G component in bytes 2..3, and
  //!        a 16-bit B component in bytes 4..5.
  kR16G16B16SScaled,

  //! @brief 3 components, 48-bit unsigned integer format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, and a
  //!        16-bit B component in bytes 4..5.
  kR16G16B16UInt,

  //! @brief 3 components, 48-bit signed integer format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, and a
  //!        16-bit B component in bytes 4..5.
  kR16G16B16SInt,

  //! @brief 3 components, 48-bit signed floating-point format that has a 16-bit
  //!        R component in bytes 0..1, a 16-bit G component in bytes 2..3, and
  //!        a 16-bit B component in bytes 4..5.
  kR16G16B16SFloat,

  // 64 bit - Block size 8 byte

  //! @brief 4 components, 64-bit unsigned normalized format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16UNorm,

  //! @brief 4 components, 64-bit signed normalized format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16SNorm,

  //! @brief 4 components, 64-bit unsigned scaled integer format that has a
  //!        16-bit R component in bytes 0..1, a 16-bit G component in
  //!        bytes 2..3, a 16-bit B component in bytes 4..5, and a 16-bit A
  //!        component in bytes 6..7.
  kR16G16B16A16UScaled,

  //! @brief 4 components, 64-bit signed scaled integer format that has a 16-bit
  //!        R component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16SScaled,

  //! @brief 4 components, 64-bit unsigned integer format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16UInt,

  //! @brief 4 components, 64-bit signed integer format that has a 16-bit R
  //!        component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16SInt,

  //! @brief 4 components, 64-bit signed floating-point format that has a 16-bit
  //!        R component in bytes 0..1, a 16-bit G component in bytes 2..3, a
  //!        16-bit B component in bytes 4..5, and a 16-bit A component in
  //!        bytes 6..7.
  kR16G16B16A16SFloat,

  //! @brief 2 components, 64-bit unsigned integer format that has a 32-bit R
  //!        component in bytes 0..3, and a 32-bit G component in bytes 4..7.
  kR32G32UInt,

  //! @brief 2 components, 64-bit signed integer format that has a 32-bit R
  //!        component in bytes 0..3, and a 32-bit G component in bytes 4..7.
  kR32G32SInt,

  //! @brief 2 components, 64-bit signed floating-point format that has a 32-bit
  //!        R component in bytes 0..3, and a 32-bit G component in bytes 4..7.
  kR32G32SFloat,

  //! @brief 1 component, 64-bit unsigned integer format that has a single
  //!        64-bit R component.
  kR64UInt,

  //! @brief 1 component, 64-bit signed integer format that has a single 64-bit
  //!        R component.
  kR64SInt,

  //! @brief 1 component, 64-bit signed floating-point format that has a single
  //!        64-bit R component.
  kR64SFloat,

  // 96 bit - Block size 12 byte

  //! @brief 3 components, 96-bit unsigned integer format that has a 32-bit R
  //!        component in bytes 0..3, a 32-bit G component in bytes 4..7, and a
  //!        32-bit B component in bytes 8..11.
  kR32G32B32UInt,

  //! @brief 3 components, 96-bit signed integer format that has a 32-bit R
  //!        component in bytes 0..3, a 32-bit G component in bytes 4..7, and a
  //!        32-bit B component in bytes 8..11.
  kR32G32B32SInt,

  //! @brief 3 components, 96-bit signed floating-point format that has a 32-bit
  //!        R component in bytes 0..3, a 32-bit G component in bytes 4..7, and
  //!        a 32-bit B component in bytes 8..11.
  kR32G32B32SFloat,

  // 128 bit - Block size 16 byte

  //! @brief 4 components, 128-bit unsigned integer format that has a 32-bit R
  //!        component in bytes 0..3, a 32-bit G component in bytes 4..7, a
  //!        32-bit B component in bytes 8..11, and a 32-bit A component in
  //!        bytes 12..15.
  kR32G32B32A32UInt,

  //! @brief 4 components, 128-bit signed integer format that has a 32-bit R
  //!        component in bytes 0..3, a 32-bit G component in bytes 4..7, a
  //!        32-bit B component in bytes 8..11, and a 32-bit A component in
  //!        bytes 12..15.
  kR32G32B32A32SInt,

  //! @brief 4 components, 128-bit signed floating-point format that has a
  //!        32-bit R component in bytes 0..3, a 32-bit G component in
  //!        bytes 4..7, a 32-bit B component in bytes 8..11, and a 32-bit A
  //!        component in bytes 12..15.
  kR32G32B32A32SFloat,

  //! @brief 2 components, 128-bit unsigned integer format that has a 64-bit R
  //!        component in bytes 0..7, and a 64-bit G component in bytes 8..15.
  kR64G64UInt,

  //! @brief 2 components, 128-bit signed integer format that has a 64-bit R
  //!        component in bytes 0..7, and a 64-bit G component in bytes 8..15.
  kR64G64SInt,

  //! @brief 2 components, 128-bit signed floating-point format that has a
  //!        64-bit R component in bytes 0..7, and a 64-bit G component in
  //!        bytes 8..15.
  kR64G64SFloat,

  // 192 bit - Block size 24 byte

  //! @brief 3 components, 192-bit unsigned integer format that has a 64-bit R
  //!        component in bytes 0..7, a 64-bit G component in bytes 8..15, and a
  //!        64-bit B component in bytes 16..23.
  kR64G64B64UInt,

  //! @brief 3 components, 192-bit signed integer format that has a 64-bit R
  //!        component in bytes 0..7, a 64-bit G component in bytes 8..15, and a
  //!        64-bit B component in bytes 16..23.
  kR64G64B64SInt,

  //! @brief 3 components, 192-bit signed floating-point format that has a
  //!        64-bit R component in bytes 0..7, a 64-bit G component in
  //!        bytes 8..15, and a 64-bit B component in bytes 16..23.
  kR64G64B64SFloat,

  // 256 bit - Block size 32 byte

  //! @brief 4 components, 256-bit unsigned integer format that has a 64-bit R
  //!        component in bytes 0..7, a 64-bit G component in bytes 8..15, a
  //!        64-bit B component in bytes 16..23, and a 64-bit A component in
  //!        bytes 24..31.
  kR64G64B64A64UInt,

  //! @brief 4 components, 256-bit signed integer format that has a 64-bit R
  //!        component in bytes 0..7, a 64-bit G component in bytes 8..15, a
  //!        64-bit B component in bytes 16..23, and a 64-bit A component in
  //!        bytes 24..31.
  kR64G64B64A64SInt,

  //! @brief 4 components, 256-bit signed floating-point format that has a
  //!        64-bit R component in bytes 0..7, a 64-bit G component in
  //!        bytes 8..15, a 64-bit B component in bytes 16..23, and a 64-bit A
  //!        component in bytes 24..31.
  kR64G64B64A64SFloat,
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_ENUMS_H_