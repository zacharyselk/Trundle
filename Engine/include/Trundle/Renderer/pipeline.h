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
/// Defines a rendering pipeline.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/color.h>
#include <Trundle/Core/pointer.h>
#include <Trundle/Renderer/shader.h>

namespace Trundle {

//===-- Pipeline ----------------------------------------------------------===//
/// @brief API for a rendering pipeline.
///
/// An abstract object that allows for the representation and construction of
/// a rendering pipeline, which consists of a series of connected shaders.
//===----------------------------------------------------------------------===//
class Pipeline {
public:
  /// @brief Static constructor.
  ///
  /// Creates a new rendering pipeline.
  /// @param[in] renderer The renderer to use for creating the pipeline.
  /// @return A reference to a newly created pipeline object.
  static Ref<Pipeline> create(const Ref<Renderer> renderer);

  /// @brief Default destructor.
  virtual ~Pipeline() = 0;

  /// @brief Adds a new shader to the pipeline.
  ///
  /// Adds (or overwrites) a stage in the rendering pipeline with the shader.
  /// If a shader of the same @ref ShaderType is already in the pipeline it
  /// will be overwritten by the new shader of that type.
  /// @param[in] shader The shader to add to the rendering pipeline.
  virtual void addShader(const Ref<Shader> shader) = 0;

  /// @brief Links the shaders in the pipeline.
  ///
  /// Links together all the shaders in the pipeline into a single execuatble
  /// that can be run in the backend.
  virtual void link() = 0;

  /// @brief Binds the pipeline so that it will be used for rendering.
  ///
  /// Sets the pipeline executable as being the current rendering state that
  /// all future draw commands will use.
  virtual void bind() = 0;

  /// @brief Sets a vec4f uniform in the shader.
  ///
  /// @param[in] name The variable name.
  /// @param[in] data The data to set the variable to.
  virtual void setVec4f(std::string name, std::array<float, 4> data) = 0;
};

} // namespace Trundle