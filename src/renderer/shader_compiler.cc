// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "shader_compiler.h"

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include "shader.h"

namespace chr::renderer {

static shaderc_shader_kind shaderStageToShaderC(ShaderStage stage) {
  switch (stage) {
    case ShaderStage::kVertex:
      return shaderc_glsl_vertex_shader;
    case ShaderStage::kFragment:
      return shaderc_glsl_fragment_shader;
    case ShaderStage::kCompute:
      return shaderc_glsl_compute_shader;
    default:
      break;
  }

  debug::Assert(false, "Unsupported shader type");

  return static_cast<shaderc_shader_kind>(0);
}

std::vector<uint8_t> CompileShader(std::vector<uint8_t> source,
                                   const std::string& filepath,
                                   ShaderStage type) {
  shaderc::Compiler compiler;
  shaderc::CompileOptions options;

  options.SetTargetEnvironment(shaderc_target_env_vulkan,
                               shaderc_env_version_vulkan_1_2);
  options.SetOptimizationLevel(shaderc_optimization_level_performance);

  shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(
      std::bit_cast<char*>(source.data()), shaderStageToShaderC(type),
      filepath.c_str(), options);

  // TODO: improve logging with full errors and warnings
  if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
    log::Err("{}", module.GetErrorMessage());
  }

  std::vector<uint8_t> result;
  result.resize((module.end() - module.begin()) * 4);
  memcpy(result.data(), module.begin(), result.size());

  return result;
}

}  // namespace chr::renderer