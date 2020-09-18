//===-- primitive.h -------------------------------------------------------===//
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
// A collection of helper classes to build and maintian primative shapes.
// TODO: Create abstract Primitive class.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/core.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/sceneRenderer.h>
#include <Trundle/Render/shader.h>
#include <Trundle/common.h>

#include <glm/glm.hpp>

namespace Trundle {

// Temporary
template <typename T> struct Coord2d {
  Coord2d(T x, T y) : x(x), y(y) {}
  T x;
  T y;
};

//===-- Triangle ----------------------------------------------------------===//
// Holds a representaion of a triangle.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Triangle {
public:
  Triangle(float base = 1.0, float height = 1.0);
  Triangle(glm::vec3 verts[3]);

  void setPosition(float x, float y);
  void set(const std::string& variable, uniform_t values);
  void setWidth(float w);
  void setHeight(float h);
  void setShader(const Shader& s);

  IndexBuffer getIndexBuffer(const Renderer& r) const;
  VertexBuffer getVertexBuffer(const Renderer& r) const;

  glm::vec3 center;
  glm::vec3 vertices[3];

  friend class SceneRenderer;

private:
  // TODO: Change vec4 to variant
  std::unordered_map<std::string, uniform_t> attributes;
  Shader shader;
  float width, height;

  void calculateVertices();
};

//===-- Quad --------------------------------------------------------------===//
// Holds a representaion of a square.
//===----------------------------------------------------------------------===//
// struct Quad {
//   Quad(float width, float height);
//   Quad(glm::vec3 verts[4]);

//   void setPosition(float x, float y, float z = 0.0f);

//   glm::vec3 center;
//   glm::vec3 vertices[6];
// };

} // namespace Trundle