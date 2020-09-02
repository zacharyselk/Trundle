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
// Defines the shader APIs for the backend graphics.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/util.h>
#include <Trundle/common.h>

#include <glm/glm.hpp>

namespace Trundle {

// Forward declare the backend implementations.
namespace OpenGL {
class Shader;
}

//===-- Uniform -----------------------------------------------------------===//
// A struct that defines a uniform by name and with a data type.
// TODO: Currently using a fixed size matrix, need to use a std::variant
//===----------------------------------------------------------------------===//
struct Uniform {
  Uniform(std::string str, glm::mat4 mat) : name(str), matrix(mat) {}

  std::string name;
  glm::mat4 matrix;
};

//===-- Shader ------------------------------------------------------------===//
// API for a shader.
//===----------------------------------------------------------------------===//
class Shader {
public:
  Shader() = default;
  Shader(const Renderer& r, const std::string& vertexShader,
         const std::string& fragmentShader, const Uniform& uniform);
  Shader& operator=(const Shader& shader) noexcept {
    vptr = shader.vptr;
    return *this;
  }

  void bind() const { vptr->bind(); }
  void unbind() const { vptr->unbind(); }

  friend class OpenGL::Shader;

private:
  // Virtual base class for polymorphism.
  class ShaderConcept {
  public:
    virtual ~ShaderConcept() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
  };

  // Custom virtual pointer to allow for value semantic polymorphism.
  std::shared_ptr<const ShaderConcept> vptr;
};

} // namespace Trundle