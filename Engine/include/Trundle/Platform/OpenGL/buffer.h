//===-- buffer.h ----------------------------------------------------------===//
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
/// Defines the buffer containers for the OpenGL backend.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Renderer/buffer.h>

namespace Trundle::OpenGL {

//===-- IndexBuffer -------------------------------------------------------===//
/// @brief Container that holds the rendering order for verticies.
//===----------------------------------------------------------------------===//
class IndexBuffer : public Trundle::IndexBuffer {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] indices The indices and the order in which to render them.
  /// @param[in] count The number of indices passed.
  IndexBuffer(std::vector<uint32_t> indices);

  /// @brief Default destructor.
  virtual ~IndexBuffer();

  /// @brief Sets this index buffer as the current rendering index buffer.
  ///
  /// When called the index buffer that this object represents will be set to
  /// be the current index buffer the the backend will use for all draw calls.
  virtual void bind();

private:
  // Unique id of the buffer given by opengl.
  uint32_t id;
};

//===-- VertexBuffer ------------------------------------------------------===//
/// @brief Container that holds the coordinate information for the vertices.
//===----------------------------------------------------------------------===//
class VertexBuffer : public Trundle::VertexBuffer {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] vertices An array of coordinates describing the vertex
  ///                     position.
  /// @param[in] layout A layout descriptor of the vertices coordinates.
  /// @param[in] size The number of vertices.
  VertexBuffer(const std::vector<float> vertices,
               const Ref<BufferLayout> layout);

  virtual ~VertexBuffer();

  virtual void bind();

  virtual Ref<BufferLayout> getLayout();

private:
  uint32_t id;
  Ref<BufferLayout> layout;
};

//===-- VertexArray -------------------------------------------------------===//
/// @brief Container that holds an array that references an @ref IndexBuffer
///        and a series of @ref VertexBuffers that form an array of shapes
///        to be drawn.
//===----------------------------------------------------------------------===//
class VertexArray : public Trundle::VertexArray {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] indexBuffer The index buffer describing the vertex ordering.
  /// @param[in] vertexBuffers A list of vertex buffers.
  VertexArray(Ref<Trundle::IndexBuffer> indexBuffer,
              std::vector<Ref<Trundle::VertexBuffer>> vertexBuffers);

  virtual ~VertexArray();

  virtual void bind();

private:
  uint32_t id;
  Ref<Trundle::IndexBuffer> indexBuffer;
  std::vector<Ref<Trundle::VertexBuffer>> vertexBuffers;
};

} // namespace Trundle::OpenGL