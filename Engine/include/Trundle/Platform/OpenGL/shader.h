//===-- shader.h ----------------------------------------------------------===//
//
// Copyright 2021 Zachary Selk
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
/// Defines the shader object for the OpenGL backend.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Renderer/shader.h>

namespace Trundle::OpenGL {

//===-- Shader ------------------------------------------------------------===//
/// @brief Interface for a shader object.
///
/// An abstract object that allows for manipulation of shaders in OpenGL.
//===----------------------------------------------------------------------===//
class Shader : public Trundle::Shader {
public:
  Shader() = delete;

  /// @brief Default constructor.
  ///
  /// @param[in] type The type of shader this object represents.
  Shader(Trundle::ShaderType type);

  /// @brief Default destructor.
  ~Shader();

  /// @brief Load the shader code from a string.
  ///
  /// Sets the shader code of this object to the string passed.
  /// @param[in] shader A string of the shader code.
  virtual void loadString(const std::string& shader);

  /// @brief Loads the shader code from a file.
  ///
  /// Reads shader file contents and loads it into memory.
  /// @param[in] filename The name of the file to load.
  virtual void loadFile(const std::string& filename);

  /// @brief Compiles the shader code.
  ///
  /// The shader source code is compiled into a binary the the rendering
  /// backend can use.
  virtual void compile();

  /// @brief Getter function for the shader type.
  ///
  /// @return The type of shader that this object represents.
  virtual Trundle::ShaderType getType();

  /// @brief Getter function for the shader id.
  ///
  /// @return The id of this shader assigned by the opengl backend.
  virtual uint32_t getId();

private:
  // The type of shader this is.
  Trundle::ShaderType type;
  // The source code of the shader.
  const char* source;
  // The unique id of the shader assigned by opengl.
  uint32_t id;
};

} // namespace Trundle::OpenGL