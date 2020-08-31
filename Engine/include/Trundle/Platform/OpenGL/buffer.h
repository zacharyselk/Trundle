//===-- buffer.h ----------------------------------------------------------===//
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
// OpenGL implementation of the buffers rendering API.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Render/buffer.h>

namespace Trundle::OpenGL {

//===-- IndexBuffer -------------------------------------------------------===//
// A buffer that contains vertexes and the order to render them in.
//===----------------------------------------------------------------------===//
class IndexBuffer : public Trundle::IndexBuffer::IndexBufferConcept {
public:
  IndexBuffer(uint32_t* indices, uint32_t count);
  virtual ~IndexBuffer();

  virtual void bind() const override final;
  virtual void unbind() const override final;

  virtual size_t size() const override final;

private:
  uint32_t id;
  size_t count;
};

//===-- VertexBuffer ------------------------------------------------------===//
// A buffer that contains information for the vertex shader.
//===----------------------------------------------------------------------===//
class VertexBuffer : public Trundle::VertexBuffer::VertexBufferConcept {
public:
  VertexBuffer(float* vertices, const BufferLayout& layout, uint32_t size);
  virtual ~VertexBuffer();

  virtual const BufferLayout& getLayout() const override final;

  virtual void bind() const override final;
  virtual void unbind() const override final;

private:
  uint32_t id;
  BufferLayout layout;
};

//===-- VertexArray -------------------------------------------------------===//
// Defines a vertex array which references an index buffer and a list of
// vertex buffers used for rendering.
//===----------------------------------------------------------------------===//
class VertexArray : public Trundle::VertexArray::VertexArrayConcept {
public:
  VertexArray(const std::vector<Trundle::VertexBuffer>& vertexBuffers,
              const Trundle::IndexBuffer& indexBuffers);
  virtual ~VertexArray();

  void bind() const override final;
  void unbind() const override final;
  virtual const std::shared_ptr<std::vector<Trundle::VertexBuffer>>&
  getVertexBuffers() const override final;
  virtual const std::shared_ptr<Trundle::IndexBuffer>&
  getIndexBuffer() const override final;

private:
  uint32_t id;
  std::shared_ptr<std::vector<Trundle::VertexBuffer>> vertexBuffers;
  std::shared_ptr<Trundle::IndexBuffer> indexBuffer;
};

} // namespace Trundle::OpenGL