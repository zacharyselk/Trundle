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

#include <Trundle/Core/core.h>
#include <Trundle/Core/log.h>
#include <Trundle/Render/camera.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/util.h>
#include <Trundle/common.h>

#include <glm/glm.hpp>

namespace Trundle {

// Forward declare the backend implementations.
namespace OpenGL {
class Shader;
class Uniform;
} // namespace OpenGL

class Uniform;

//===-- Shader ------------------------------------------------------------===//
// API for a shader.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Shader {
public:
  Shader() = default;
  Shader(const Shader&) = default;
  Shader(const Renderer& r, const std::string& vertexShader,
         const std::string& fragmentShader);
  Shader& operator=(const Shader& shader) noexcept {
    vptr = shader.vptr;
    return *this;
  }

  void bind() const { vptr->bind(); }
  void unbind() const { vptr->unbind(); }

  static Shader create(const Renderer& r, const std::string& vertexShader,
                       const std::string& fragmentShader);

  friend class OpenGL::Shader;
  friend class Trundle::Uniform;

protected:
  uint32_t getId() const { return vptr->getId(); }

private:
  // Virtual base class for polymorphism.
  class ShaderConcept {
  public:
    virtual ~ShaderConcept() = default;

    virtual std::shared_ptr<const ShaderConcept> move() const = 0;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getId() const = 0;
  };

  // Custom virtual pointer to allow for value semantic polymorphism.
  std::shared_ptr<const ShaderConcept> vptr;
};

//===-- Uniform -----------------------------------------------------------===//
// A struct that defines a uniform by name and with a data type.
// TODO: Currently using a fixed size matrix, need to use a std::variant
//===----------------------------------------------------------------------===//
using uniform_t = std::variant<glm::vec3, glm::vec4, glm::mat4>;
class Uniform {
public:
  Uniform(const Renderer& r, const std::string& uniformName,
          const uniform_t& uniformData);

  // Bind the uniform to a shader.
  void bind(const Shader& shader) const {
    shader.bind();
    vptr->bind(shader.getId());
  }
  void unbind() const { vptr->unbind(); }

  friend class OpenGL::Uniform;

private:
  // Virtual base class for polymorphism.
  class UniformConcept {
  public:
    virtual ~UniformConcept() = default;

    virtual void bind(uint32_t shaderId) const = 0;
    virtual void unbind() const = 0;
  };

  // Custom virtual pointer to allow for value semantic polymorphism.
  std::shared_ptr<const UniformConcept> vptr;
};

} // namespace Trundle