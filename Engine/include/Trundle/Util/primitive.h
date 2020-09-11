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
//
//===----------------------------------------------------------------------===//
#pragma once

#include <glm/glm.hpp>

namespace Trundle {

//===-- Triangle ----------------------------------------------------------===//
// Holds a representaion of a triangle and can return
//===----------------------------------------------------------------------===//
struct Triangle {
  Triangle(float base, float height);
  Triangle(glm::vec3 verts[3]);

  void setPosition(float x, float y, float z = 0.0f);

  glm::vec3 center;
  glm::vec3 vertices[3];
};

} // namespace Trundle