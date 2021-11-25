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
/// Defines the shader APIs for the backend graphics to define a shader object.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/pointer.h>
#include <Trundle/Core/util.h>
#include <Trundle/Renderer/renderer.h>

namespace Trundle {

//===-- ShaderType --------------------------------------------------------===//
/// @brief Categories of the different types of shaders.
//===----------------------------------------------------------------------===//
enum class ShaderType { None = 0, FragmentShader, VertexShader, ComputeShader };

//===-- Shader ------------------------------------------------------------===//
/// @brief API for a shader object.
///
/// An abstract object that allows for cross-backend manipulation of shaders.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Shader {
public:
  /// @brief Static constructor
  ///
  /// Creates a shader.
  /// @param[in] renderer The renderer to use for creating the shader.
  /// @param[in] type The type of shader to classify this object as.
  /// @return A reference to a newly created shader object.
  static Ref<Shader> create(const Ref<Renderer> renderer, ShaderType type);

  /// @brief Default destructor.
  virtual ~Shader() = 0;

  /// @brief Load the shader code from a string.
  ///
  /// Sets the shader code of this object to the string passed.
  /// @param[in] shader A string of the shader code.
  virtual void loadString(const std::string& shader) = 0;

  /// @brief Loads the shader code from a file.
  ///
  /// Reads shader file contents and loads it into memory.
  /// @param[in] filename The name of the file to load.
  virtual void loadFile(const std::string& filename) = 0;

  /// @brief Compiles the shader code.
  ///
  /// The shader source code is compiled into a binary the the rendering
  /// backend can use.
  virtual void compile() = 0;

  /// @brief Getter function for the shader type
  ///
  /// @return The type of shader that this object represents.
  virtual Trundle::ShaderType getType() = 0;

  /// @brief Getter function for the shader id.
  ///
  /// @return The id of this shader assigned by the opengl backend.
  virtual uint32_t getId() = 0;
};

} // namespace Trundle