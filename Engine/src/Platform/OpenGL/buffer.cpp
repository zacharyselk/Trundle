//===-- buffer.cpp --------------------------------------------------------===//
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
#include <GL/gl3w.h>
#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Platform/OpenGL/util.h>

namespace Trundle::OpenGL {

//===-- IndexBuffer -------------------------------------------------------===//
IndexBuffer::IndexBuffer(std::vector<uint32_t> indices) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
               indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &id); }

void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
//===----------------------------------------------------------------------===//

//===-- VertexBuffer ------------------------------------------------------===//
VertexBuffer::VertexBuffer(const std::vector<float> vertices,
                           const Ref<BufferLayout> layout)
    : id(0), layout(layout) {
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id); }

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

Ref<BufferLayout> VertexBuffer::getLayout() { return layout; }
//===----------------------------------------------------------------------===//

//===-- VertexArray -------------------------------------------------------===//
VertexArray::VertexArray(Ref<Trundle::IndexBuffer> indexBuffer,
                         std::vector<Ref<Trundle::VertexBuffer>> vertexBuffers)
    : id(0), indexBuffer(indexBuffer), vertexBuffers(vertexBuffers) {
  glGenVertexArrays(1, &id);
  glBindVertexArray(id);
  indexBuffer->bind();

  for (auto& buffer : vertexBuffers) {
    buffer->bind();
    auto layout = buffer->getLayout();
    for (uint32_t i = 0; i < layout->size(); ++i) {
      glVertexAttribPointer(
          i, (*layout)[i]->numberOfComponents, toOpenGL((*layout)[i]->type),
          (*layout)[i]->normalize ? GL_TRUE : GL_FALSE, layout->getStride(),
          (void*)static_cast<uint64_t>((*layout)[i]->offset));
      glEnableVertexAttribArray(static_cast<int>(i));
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

VertexArray::~VertexArray() { glDeleteBuffers(1, &id); }

void VertexArray::bind() { glBindVertexArray(id); }
//===----------------------------------------------------------------------===//

} // namespace Trundle::OpenGL