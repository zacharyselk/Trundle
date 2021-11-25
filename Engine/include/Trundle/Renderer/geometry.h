//===-- geometry.h --------------------------------------------------------===//
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
/// A collection of geometry containers.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <glm/glm.hpp>
#include <Trundle/common.h>
#include <Trundle/Core/util.h>

namespace Trundle {

//===-- Point2D -----------------------------------------------------------===//
/// @brief A point in 2 dimentional space.
//===----------------------------------------------------------------------===//
template <typename T> struct Point2D {
  Point2D() = default;
  Point2D(T x, T y) : x(x), y(y) {}

  T x{}, y{};
};

//===-- Point3D -----------------------------------------------------------===//
/// @brief A point in 3 dimentional space.
//===----------------------------------------------------------------------===//
template <typename T> struct Point3D {
  Point3D() = default;
  Point3D(T x, T y, T z) : x(x), y(y), z(z) {}

  T x{}, y{}, z{};
};

//===-- Shape -------------------------------------------------------------===//
/// @brief An abstract parent class for a geometrical shape.
//===----------------------------------------------------------------------===//
template <typename T, uint64_t N>
class Shape {
public:
  virtual void draw() = 0;

//protected:
  std::array<T, N> points;
  glm::mat4 modelMatrix;
};

//===-- Rect --------------------------------------------------------------===//
/// @brief A rectangle in 2 dimentional space containing 4 points.
//===----------------------------------------------------------------------===//
template <typename T> class Rect : public Shape<Point2D<T>, 4> {
  using point = Point2D<T>;
  using Shape<point, 4>::points;
public:
  Rect(point bottomLeft, point topRight) {
    points[0] = bottomLeft;
    points[1] = {bottomLeft.x, topRight.y};
    points[2] = topRight;
    points[3] = {topRight.x, bottomLeft.y};
  }

  Rect(point bottomLeft, T width, T height) {
    points[0] = bottomLeft;
    points[1] = {bottomLeft.x, bottomLeft.y+height};
    points[2] = {bottomLeft.x+width, bottomLeft.y+height};
    points[3] = {bottomLeft.x+width, bottomLeft.y};
  }

  virtual void draw() override {
    points[0] = {0,0};
  }
};

template class Rect<int>;

} // namespace Trundle