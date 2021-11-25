//===-- renderer.h --------------------------------------------------------===//
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

namespace Trundle {

//===-- RenderingBackend --------------------------------------------------===//
/// @brief Defines the available backends that the renderer can use.
//===----------------------------------------------------------------------===//
enum class RenderingBackend { None = 0, OpenGL, Headless };

//===-- Renderer ----------------------------------------------------------===//
/// @brief Contains information for the rendering system.
///
/// Behaves like a cookie and allows the rendering API to make decisions on
/// how to create and render objects.
//===----------------------------------------------------------------------===//
class Renderer {
public:
  Renderer() = delete;

  /// @brief Default constructor.
  ///
  /// @param[in] backend The backend that this renderer should use.
  Renderer(RenderingBackend backend);

  RenderingBackend getBackend();

private:
  RenderingBackend backend;
};

} // namespace Trundle