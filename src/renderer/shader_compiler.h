// Copyright (c) 2022 Sandro Cavazzoni.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.

#ifndef CHR_RENDERER_SHADER_COMPILER_H_
#define CHR_RENDERER_SHADER_COMPILER_H_

#include "pch.h"

namespace chr::renderer {

enum class ShaderStage;

std::vector<uint8_t> CompileShader(std::vector<uint8_t> source,
                                   const std::string& filepath,
                                   ShaderStage type);

}  // namespace chr::renderer

#endif  // CHR_RENDERER_SHADER_COMPILER_H_