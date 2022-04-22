// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#include "shader_compiler.h"

#include <regex>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include "shader.h"

namespace chr::renderer {

static shaderc_shader_kind GetSpirvShader(ShaderStage stage) {
  switch (stage) {
    case ShaderStage::kVertex:
      return shaderc_vertex_shader;
    case ShaderStage::kFragment:
      return shaderc_fragment_shader;
    case ShaderStage::kCompute:
      return shaderc_compute_shader;
    default:
      break;
  }

  debug::Assert(false, "Unsupported shader type");

  return static_cast<shaderc_shader_kind>(0);
}

static shaderc_source_language GetSpirvLanguage(SourceLanguage language) {
  switch (language) {
    case SourceLanguage::kGlsl:
      return shaderc_source_language_glsl;
    case SourceLanguage::kHlsl:
      return shaderc_source_language_hlsl;
    default:
      break;
  }

  debug::Assert(false, "Unsupported language type");

  return static_cast<shaderc_source_language>(0);
}

static shaderc_optimization_level GetSpirvOptimizationLevel(
    OptimizationLevel optimization_level) {
  switch (optimization_level) {
    case OptimizationLevel::kNone:
      return shaderc_optimization_level_zero;
    case OptimizationLevel::kSize:
      return shaderc_optimization_level_size;
    case OptimizationLevel::kPerformance:
      return shaderc_optimization_level_performance;
    default:
      break;
  }

  debug::Assert(false, "Unsupported optimization level");

  return static_cast<shaderc_optimization_level>(0);
}

auto ShaderCompiler::Compile(std::vector<uint8_t> source,
                             const std::string& filename, ShaderStage type,
                             CompileSharerOptions options) const
    -> CompileShaderResult {
  CompileShaderResult result;
  shaderc::Compiler spriv_compiler;
  shaderc::CompileOptions spirv_options;

  spirv_options.SetTargetEnvironment(shaderc_target_env_vulkan,
                                     shaderc_env_version_vulkan_1_2);
  spirv_options.SetOptimizationLevel(
      GetSpirvOptimizationLevel(options.optimization));
  spirv_options.SetSourceLanguage(GetSpirvLanguage(options.language));

  if (options.warning_as_errors) {
    spirv_options.SetWarningsAsErrors();
  }

  auto spirv_compiler_result = spriv_compiler.CompileGlslToSpv(
      std::bit_cast<char*>(source.data()), source.size(), GetSpirvShader(type),
      filename.c_str(), spirv_options);

  result.success = spirv_compiler_result.GetCompilationStatus() ==
                   shaderc_compilation_status_success;

  std::stringstream stream_message(spirv_compiler_result.GetErrorMessage());
  std::string segment;
  const std::regex error_regex(".*:\\d+: error:.*");
  const std::regex warning_regex(".*:\\d+: warning:.*");

  while (std::getline(stream_message, segment, '\n')) {
    if (std::regex_match(segment, error_regex)) {
      log::Err("{}", segment);
      result.errors.push_back(segment);
    } else if (std::regex_match(segment, warning_regex)) {
      log::Warn("{}", segment);
      result.warnings.push_back(segment);
    } else {
      log::Info("{}", segment);
      result.infos.push_back(segment);
    }
  }

  result.data.resize(
      (spirv_compiler_result.end() - spirv_compiler_result.begin()) * 4);
  memcpy(result.data.data(), spirv_compiler_result.begin(), result.data.size());

  return result;
}

}  // namespace chr::renderer