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
  virtual void bind();
  virtual void unbind();

  static Shader create(const Renderer& r, const std::string& vertexShader,
                       const std::string& fragmentShader);
};

//===-- Uniform -----------------------------------------------------------===//
// A struct that defines a uniform by name and with a data type.
// TODO: Currently using a fixed size matrix, need to use a std::variant
//===----------------------------------------------------------------------===//
using uniform_t = std::variant<glm::vec3, glm::vec4, glm::mat4>;
class Uniform {
public:
  // Bind the uniform to a shader.
  virtual void bind(const Shader& shader);
  virtual void unbind();

  static std::shared_ptr<Uniform> create(const Renderer& r, const std::string& uniformName,
          const uniform_t& uniformData);
};

} // namespace Trundle