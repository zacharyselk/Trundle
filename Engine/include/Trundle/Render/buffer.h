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
// Defines the buffer APIs for the backend.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/util.h>
#include <Trundle/common.h>

namespace Trundle {

// Forward declare the backend implementations.
namespace OpenGL {
class IndexBuffer;
class VertexBuffer;
class VertexArray;
} // namespace OpenGL


//===-- LayoutElement -----------------------------------------------------===//
// A structure for defining how the layout of a vertex (element) is defined.
// TODO: Possibly should be moved somewhere else, either into LayoutElement
//       if it is the only one who uses this, otherwise maybe into
//       Render/util.h
// TODO: Check to see if this object is being copy constructed.
//===----------------------------------------------------------------------===//
struct LayoutElement {
  LayoutElement(const Rendering::GraphicsType& type, const std::string& name,
                const bool& normalize = false);
  LayoutElement(const uint32_t& osffset, const Rendering::GraphicsType& type,
                const std::string& name, const bool& normalize = false);
  LayoutElement(const LayoutElement& elem, const uint32_t& offset);
  LayoutElement(const LayoutElement& element) = default;

  Rendering::GraphicsType type;
  std::string name;
  uint32_t elementSize;
  uint32_t numberOfComponents;
  uint32_t offset;
  bool normalize;
};

//===-- BufferLayout ------------------------------------------------------===//
// Constructs and calculates a genaric layout specification for a buffer.
//===----------------------------------------------------------------------===//
class BufferLayout {
public:
  BufferLayout() = default;
  BufferLayout(const std::initializer_list<LayoutElement>& layout);
  BufferLayout(const BufferLayout& layout) = default;
  BufferLayout(BufferLayout&&) noexcept = default;

  uint32_t getStride() const { return stride; }

  const LayoutElement& operator[](size_t index) const;
  size_t size() const;
  std::vector<LayoutElement>::const_iterator begin() const;
  std::vector<LayoutElement>::const_iterator end() const;

private:
  std::shared_ptr<const std::vector<LayoutElement>> layout;
  uint32_t stride;
};

//===-- IndexBuffer -------------------------------------------------------===//
/// @brief An API for the buffer which contains vertices and the order in
///        in which they are rendered.
///
/// The @ref IndexBuffer dictates which vertices from the @ref VertexBuffer
/// are rendered and in what order they are rendered. This is an essential
/// component of the rendering system.
//===----------------------------------------------------------------------===//
class IndexBuffer {
public:
  //===--------------------------------------------------------------------===//
  /// @brief Binds the current @ref IndexBuffer 
  //===--------------------------------------------------------------------===//
  virtual void bind();
  virtual void unbind();

  virtual size_t size();

  static std::shared_ptr<IndexBuffer> create(const Renderer& r, uint32_t* indices,
                            uint32_t count);
};

//===-- VertexBuffer ------------------------------------------------------===//
// API for abuffer that contains information for the vertex shader.
//===----------------------------------------------------------------------===//
class VertexBuffer {
public:
 virtual const BufferLayout& getLayout();

  virtual void bind();
  virtual void unbind();

  static std::shared_ptr<VertexBuffer> create(const Renderer& r, float* vertices,
                             const BufferLayout& layout, uint32_t size);
};

//===-- VertexArray -------------------------------------------------------===//
// API that defines a vertex array which references an index buffer and a
// list of vertex buffers used for rendering.
//===----------------------------------------------------------------------===//
class VertexArray {
public:
  virtual void bind();
  virtual void unbind();
  virtual std::shared_ptr<std::vector<VertexBuffer>>& getVertexBuffers();
  virtual std::shared_ptr<IndexBuffer>& getIndexBuffer();

  static std::shared_ptr<VertexArray> create(const Renderer& r, const IndexBuffer& indexBuffer,
                            const std::vector<VertexBuffer>& vertexBuffers);
  static std::shared_ptr<VertexArray> create(const Renderer& r, const IndexBuffer& indexBuffer,
                            const VertexBuffer& vertexBuffer);
};

} // namespace Trundle
