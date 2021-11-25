//===-- primitive.cpp -----------------------------------------------------===//
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
#include <Trundle/Util/primitives.h>

namespace Trundle {

//===-- Triangle ----------------------------------------------------------===//
Triangle::Triangle(float w, float h)
    : center(w / 2.0f, h / 2.0f, 0.0f), width(w), height(h) {
  calculateVertices();
}

Triangle::Triangle(glm::vec3 verts[3])
    : center((verts[0].x + verts[1].x + verts[2].x) / 3,
             (verts[0].y + verts[1].y + verts[2].y) / 3,
             (verts[0].z + verts[1].z + verts[2].z) / 3) {
  vertices[0].position = verts[0];
  vertices[1].position = verts[1];
  vertices[2].position = verts[2];
}

void Triangle::set(const std::string& variable, uniform_t values) {
  attributes[variable] = values;
}

void Triangle::setWidth(float w) {
  width = w;
  calculateVertices();
}

void Triangle::setHeight(float h) {
  height = h;
  calculateVertices();
}

void Triangle::setShader(const Shader& s) { shader = s; }

void Triangle::setPosition(float x, float y) {
  center[0] = x;
  center[1] = y;
  calculateVertices();
}

void Triangle::calculateVertices() {
  vertices[0].position = glm::vec3(center[0] - (width / 2), center[1] - (height / 2),
                          0.0f); // Bottom left.
  vertices[1].position = glm::vec3(center[0] + (width / 2), center[1] - (height / 2),
                          0.0f); // Bottom right.
  vertices[2].position = glm::vec3(center[0], center[1] + (height / 2), 0.0f); // Top

  // TODO: Handle rotation
}

std::shared_ptr<IndexBuffer> Triangle::getIndexBuffer(const Renderer& r) const {
  uint32_t indices[3] = {0, 1, 2};
  std::shared_ptr<IndexBuffer> buf = IndexBuffer::create(r, indices, 3);
  return buf;
}

std::shared_ptr<VertexBuffer> Triangle::getVertexBuffer(const Renderer& r) const {
  float verts[3 * 3] = {vertices[0].position[0], vertices[0].position[1], vertices[0].position[2],
                        vertices[1].position[0], vertices[1].position[1], vertices[1].position[2],
                        vertices[2].position[0], vertices[2].position[1], vertices[2].position[2]};

  BufferLayout layout{{Trundle::Rendering::Float3, "position"}};
  std::shared_ptr<VertexBuffer> buf = VertexBuffer::create(r, verts, layout, sizeof(verts));
  return buf;
}

//===----------------------------------------------------------------------===//

//===-- Quad --------------------------------------------------------------===//
// Quad::Quad(float width, float height) {}

// Quad::Quad(glm::vec3 verts[4])
//     : center((verts[0].x + verts[1].x + verts[2].x + verts[3].x) / 4,
//              (verts[0].y + verts[1].y + verts[2].y + verts[3].y) / 4,
//              (verts[0].z + verts[1].z + verts[2].z + verts[3].z) / 4) {
//   vertices[0] = verts[0];
//   vertices[1] = verts[1];
//   vertices[2] = verts[1];
//   vertices[3] = verts[2];
//   vertices[4] = verts[3];
//   vertices[5] = verts[4];
// }

// void Quad::setPosition(float x, float y, float z) {
//   glm::vec3 pos(x, y, z);
//   glm::vec3 diff = center - pos;
//   vertices[0] += diff;
//   vertices[1] += diff;
//   vertices[2] += diff;
//   vertices[3] += diff;
//   vertices[4] += diff;
//   vertices[5] += diff;
//   center = pos;
// }
//===----------------------------------------------------------------------===//

} // namespace Trundle