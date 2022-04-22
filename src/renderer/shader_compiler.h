// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_COMPILER_H_
#define CHR_RENDERER_SHADER_COMPILER_H_

#include "pch.h"

namespace chr::renderer {

enum class ShaderStage;

//! @brief Compiler optimization level for shader compiler.
enum class OptimizationLevel {
  kNone,        //!< No optimization.
  kSize,        //!< Optimization for better size.
  kPerformance  //!< Optimization for better performance.
};

//! @brief Source language for shader files.
enum class SourceLanguage {
  kGlsl,  //!< GLSL shader language.
  kHlsl   //!< HLSL shader language.
};

//! @brief Options for shader compiler.
struct CompileSharerOptions {
  //! @brief Compiler optimization level
  OptimizationLevel optimization{OptimizationLevel::kPerformance};

  //! @brief Shader file source language
  SourceLanguage language{SourceLanguage::kGlsl};

  //! @brief Treats all compiler warnings as errors.
  bool warning_as_errors{false};
};

//! @brief Result object for shader compile that contain the compiler output and
//!        messages.
struct CompileShaderResult {
  //! @brief It's true if the shader is compiled correctly.
  bool success{false};

  //! @brief Compiler error messages.
  std::vector<std::string> errors{};

  //! @brief Compiler warning messages.
  std::vector<std::string> warnings{};

  //! @brief Compiler info messages.
  std::vector<std::string> infos{};

  //! @brief Shader compiled binary data.
  std::vector<uint8_t> data{};
};

//! @brief Compiler for shader files.
struct ShaderCompiler {
  //! @brief Compile a shader file into binary format.
  //! @param source Shader source file data.
  //! @param filename Shader source file name. It's used for logging and doesn't
  //!                 necessarily have to be a 'file name'.
  //! @param type Type of the shader to compile (vertex/fragment/etc.).
  //! @param options Additional options (optional) for tune shader compiler.
  //! @return Compilation result.
  auto Compile(std::vector<uint8_t> source, const std::string& filename,
               ShaderStage type, CompileSharerOptions options = {}) const
      -> CompileShaderResult;
};

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_COMPILER_H_