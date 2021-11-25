//===-- render2D.h --------------------------------------------------------===//
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
/// A 2D rendering API.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/color.h>
#include <Trundle/Core/pointer.h>
#include <glm/glm.hpp>

namespace Trundle {

//===-- Render2D ----------------------------------------------------------===//
/// @brief API for rendering objects in 2D space
//===----------------------------------------------------------------------===//
class Render2D {
public:
  /// @brief Renders a quadrilateral in 2D space.
  ///
  /// Uses the rending api to render a quad in 2D space.
  /// @param[in] transform Defines the position and size of the quad to render.
  static void quad(const Ref<glm::mat4> transform);

  /// @brief Renders a rectangle in 2D space.
  ///
  /// Uses the rending api to render a rectangle in 2D space.
  /// @param[in] x The x position of the bottom left point of the rectangle.
  /// @param[in] y The y position of the bottom left point of the rectangle.
  /// @param[in] w The width of the rectangle.
  /// @param[in] h The height of the rectangle.
  /// @param[in] color The rgba value of the color for the rectangle.
  static void rect(float x, float y, float w, float h, const Color& c);
};

} // namespace Trundle