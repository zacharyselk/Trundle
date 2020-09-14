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
  Shader(const std::string& vertexShader, const std::string& fragmentShader);
  virtual ~Shader();

  virtual std::shared_ptr<const Trundle::Shader::ShaderConcept>
  move() const override final;
  virtual void bind() const override final;
  virtual void unbind() const override final;
  virtual uint32_t getId() const override final;

  friend class Trundle::Shader;

private:
  const uint32_t id;

  // Helper functions.

  // Compiles shader text.
  uint32_t compile(uint32_t type, const std::string& src);
};

//===-- Uniform -----------------------------------------------------------===//
// OpenGL implementation for the uniform api.
//===----------------------------------------------------------------------===//
class Uniform : public Trundle::Uniform::UniformConcept {
public:
  Uniform(const std::string& uniformName, const uniform_t& uniformData);
  virtual ~Uniform();

  virtual void bind(uint32_t shaderId) const override final;
  virtual void unbind() const override final;

private:
  const std::string name;
  const uniform_t data;
};

} // namespace Trundle::OpenGL