//===-- shader.h ----------------------------------------------------------===//
//
// Copyright 2020 Zachary Selk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// Defines the shader abstraction for OpenGL graphics.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Render/shader.h>

namespace Trundle::OpenGL {

//===-- Shader ------------------------------------------------------------===//
// OpenGL implementation for the shader api.
//===----------------------------------------------------------------------===//
class Shader : public Trundle::Shader::ShaderConcept {
public:
  Shader(const std::string& vertexShader, const std::string& fragmentShader,
         const Uniform& uniform);
  virtual ~Shader();

  virtual std::shared_ptr<const Trundle::Shader::ShaderConcept>
  move() const override final;
  virtual void bind() const override final;
  virtual void unbind() const override final;
  virtual void reset(const Uniform& uniform) const override final;

  void submitUniform(const Uniform& uniform) const;

  friend class Trundle::Shader;

private:
  const uint32_t id;

  // Helper functions.

  // Compiles shader text.
  uint32_t compile(uint32_t type, const std::string& src);
};

} // namespace Trundle::OpenGL