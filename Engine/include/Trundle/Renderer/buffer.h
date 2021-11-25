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
/// Defines the buffer primatives used for detailing render points.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/pointer.h>
#include <Trundle/Renderer/renderer.h>
#include <Trundle/Renderer/util.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- LayoutElement -----------------------------------------------------===//
// @brief A structure for defining how the layout of a vertex is defined.
//===----------------------------------------------------------------------===//
struct LayoutElement {
  LayoutElement(Rendering::DataType type, const std::string& name,
                uint32_t offset = 0, bool normalize = false);

  Rendering::DataType type;
  std::string name;
  uint32_t size;
  uint32_t numberOfComponents;
  uint32_t offset;
  bool normalize;
};

//===-- BufferLayout ------------------------------------------------------===//
/// @brief Creates and calculates a genaric layout specification for a buffer.
//===----------------------------------------------------------------------===//
class BufferLayout {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] layout The layout specification to create.
  BufferLayout(std::initializer_list<LayoutElement> list);

  /// @brief Getter function for the stride of the layout.
  ///
  /// Gets the stride which is the number of bytes that the sum of the elements
  /// occupy. Conceptually equals the sizeof(layout) if the layout was an
  /// object.
  /// @return The stride of the layout in bytes.
  uint32_t getStride() const;

  /// @brief Read only access to the layout specification.
  ///
  /// @param[in] index Which element to access, counting from 0.
  /// @return An element of the layout.
  const Ref<LayoutElement> operator[](size_t index) const;

  /// @brief The size of the layout.
  ///
  /// Gets the number of elements in the layout.
  /// @return the number of elements in the layout.
  size_t size() const;

  /// @brief Getter for the constant iterator to the layout specifaction.
  ///
  /// @return A constant iterator to the begining of the specification.
  std::vector<Ref<LayoutElement>>::const_iterator begin() const;

  /// @brief Getter for the constant iterator to the layout specifaction.
  ///
  /// @return A constant iterator to one past the end of the specification.
  std::vector<Ref<LayoutElement>>::const_iterator end() const;

private:
  // Keep a reference to the layout.
  std::vector<Ref<LayoutElement>> layout;
  // Store the stride to avoid redundant re-calculations.
  uint32_t stride;
};

//===-- IndexBuffer -------------------------------------------------------===//
/// @brief API for the buffer containing rendering order for verticies.
//===----------------------------------------------------------------------===//
class IndexBuffer {
public:
  /// @brief Static constructor.
  ///
  /// @param[in] renderer The renderer to use for creating the shader.
  /// @param[in] indices The indices and the order in which to render them.
  /// @param[in] count The number of indices passed.
  static Ref<IndexBuffer> create(const Ref<Renderer> renderer,
                                 std::vector<uint32_t> indices);

  /// @brief Default destructor
  virtual ~IndexBuffer() = 0;

  /// @brief Sets this index buffer as the current rendering index buffer.
  ///
  /// When called the index buffer that this object represents will be set to
  /// be the current index buffer the the backend will use for all draw calls.
  virtual void bind() = 0;
};

//===-- VertexBuffer ------------------------------------------------------===//
/// @brief API for the position of the vertices.
//===----------------------------------------------------------------------===//
class VertexBuffer {
public:
  /// @brief Static constructor.
  ///
  /// @param[in] renderer The renderer to use for creating the shader.
  /// @param[in] vertices An array of coordinates describing the vertex
  ///                     position.
  /// @param[in] layout A layout descriptor of the vertices coordinates.
  /// @param[in] size The number of vertices.
  static Ref<VertexBuffer> create(const Ref<Renderer> renderer,
                                  const std::vector<float> vertices,
                                  const Ref<BufferLayout> layout);

  /// @brief Default destructor
  virtual ~VertexBuffer() = 0;

  virtual void bind() = 0;

  virtual Ref<BufferLayout> getLayout() = 0;
};

//===-- VertexArray -------------------------------------------------------===//
/// @brief API for an array that references an @ref IndexBuffer and a series
///        of @ref VertexBuffers that form an array of shapes to be drawn.
//===----------------------------------------------------------------------===//
class VertexArray {
public:
  /// @brief Static constructor.
  ///
  /// @param[in] renderer The renderer to use for creating the shader.
  /// @param[in] indexBuffer The index buffer describing the vertex ordering.
  /// @param[in] vertexBuffers A list of vertex buffers.
  static Ref<VertexArray> create(const Ref<Renderer> renderer,
                                 Ref<IndexBuffer> indexBuffer,
                                 std::vector<Ref<VertexBuffer>> vertexBuffers);

  /// @brief Default destructor
  virtual ~VertexArray() = 0;

  virtual void bind() = 0;
};

} // namespace Trundle