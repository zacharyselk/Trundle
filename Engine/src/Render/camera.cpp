//===-- camera.cpp --------------------------------------------------------===//
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
#include <Trundle/Render/camera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Trundle {

//===-- OrthographicCamera ------------------------------------------------===//
OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top, float front, float back)
    : projectionMatrix(glm::ortho(left, right, bottom, top, front, back)),
      viewMatrix(1.0f) {
  viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::recalculateViewMatrix() {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), pos) *
      glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

  viewMatrix = glm::inverse(transform);
  viewProjectionMatrix = projectionMatrix * viewMatrix;
}

} // namespace Trundle