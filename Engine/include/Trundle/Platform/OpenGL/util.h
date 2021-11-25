//===-- util.h ------------------------------------------------------------===//
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
/// Helper functions for the OpenGL rendering backend.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Renderer/util.h>
#include <Trundle/common.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle::OpenGL {

// Converts a GraphicsType into an OpenGL type.
constexpr GLenum toOpenGL(Trundle::Rendering::DataType type) {
  switch (type) {
  case Trundle::Rendering::DataType::Float:
  case Trundle::Rendering::DataType::Float2:
  case Trundle::Rendering::DataType::Float3:
  case Trundle::Rendering::DataType::Float4:
  case Trundle::Rendering::DataType::Mat2:
  case Trundle::Rendering::DataType::Mat3:
  case Trundle::Rendering::DataType::Mat4:
    return GL_FLOAT;
  default:
    Log::Critical("Unknown GraphicsType");
  }

  return (GLenum)0;
}

} // namespace Trundle::OpenGL