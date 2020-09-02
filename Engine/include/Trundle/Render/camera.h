//===-- camera.h ----------------------------------------------------------===//
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
// API for creating a camera. A camera is nothing more than a projection matrix
// (in either perspective or orthographic mode) that has the ability to
// translate points in 3D space (objects in the scene) onto 2D space (the
// screen) when points are multipled by this matrix.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>
#include <Trundle/common.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Trundle {

//===-- OrthographicCamera ------------------------------------------------===//
// Uses a perspective-less projection matrix that translates points to 2D
// without taking their depth (z-position) into consideration.
//===----------------------------------------------------------------------===//
class OrthographicCamera {
public:
  // Define the boarders of the camera with raw values to create a projection
  // matrix.
  OrthographicCamera(float left, float right, float bottom, float top,
                     float front = -1.0f, float back = 1.0f);
  // Pass the camera a projection matrix that will define the translation.
  OrthographicCamera(const glm::mat4& projectionMatrix);

  const glm::vec3& getPosition() const { return pos; }
  float getRotation() const { return rotation; }
  const glm::mat4& getViewProjectionMatrix() {
    Log::Warn(glm::to_string(viewProjectionMatrix));
    return viewProjectionMatrix;
  }

  // Temporary
  void setPos(const glm::vec3& p) { pos = p; }
  void setRotation(float r) { rotation = r; }
  void recalculateViewMatrix();

private:
  glm::vec3 pos{0.0f};
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 viewProjectionMatrix;

  float rotation{0};
};

} // namespace Trundle