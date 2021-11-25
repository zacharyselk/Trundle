//===-- buffer.cpp --------------------------------------------------------===//
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
#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/util.h>

namespace Trundle {

//===-- LayoutElement -----------------------------------------------------===//
LayoutElement::LayoutElement(const Rendering::GraphicsType& type,
                             const std::string& name, const bool& normalize)
    : type(type), name(name), elementSize(Rendering::getSizeOf(type)),
      numberOfComponents(elementSize / Rendering::getComponentSizeOf(type)),
      offset(0), normalize(normalize) {}

LayoutElement::LayoutElement(const LayoutElement& elem, const uint32_t& offset)
    : LayoutElement(elem) {
  this->offset = offset;
}
//===----------------------------------------------------------------------===//

//===-- BufferLayout ------------------------------------------------------===//
BufferLayout::BufferLayout(const std::initializer_list<LayoutElement>& l)
    : stride(0) {

  std::vector<LayoutElement> list;
  for (const auto& element : l) {
    LayoutElement elem(element, stride);
    list.push_back(elem);
    stride += elem.elementSize;
  }

  layout = std::make_shared<std::vector<LayoutElement>>(std::move(list));
}

const LayoutElement& BufferLayout::operator[](size_t index) const {
  return layout->operator[](index);
}

size_t BufferLayout::size() const { return layout->size(); }

std::vector<LayoutElement>::const_iterator BufferLayout::begin() const {
  return layout->begin();
}

std::vector<LayoutElement>::const_iterator BufferLayout::end() const {
  return layout->end();
}
//===----------------------------------------------------------------------===//

//===-- IndexBuffer -------------------------------------------------------===//
std::shared_ptr<IndexBuffer> IndexBuffer::create(const Renderer& r, uint32_t* indices,
                                uint32_t count) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    assert(0 && "Error: Rendering API for IndexBuffer is None");
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::IndexBuffer>(indices, count);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

//===-- VertexBuffer ------------------------------------------------------===//
std::shared_ptr<VertexBuffer> VertexBuffer::create(const Renderer& r, float* vertices,
                                  const BufferLayout& layout, uint32_t size) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    assert(0 && "Error: Rendering API for VertexBuffer is None");
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::VertexBuffer>(vertices, layout, size);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

//===-- VertexArray -------------------------------------------------------===//
std::shared_ptr<VertexArray>
VertexArray::create(const Renderer& r, const IndexBuffer& indexBuffer,
                    const std::vector<VertexBuffer>& vertexBuffers) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    assert(0 && "Error: Rendering API for VertexArray is None");
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::VertexArray>(indexBuffer, vertexBuffers);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}

std::shared_ptr<VertexArray> VertexArray::create(const Renderer& r,
                                const IndexBuffer& indexBuffer,
                                const VertexBuffer& vertexBuffers) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    assert(0 && "Error: Rendering API for VertexArray is None");
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::VertexArray>(indexBuffer, vertexBuffers);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

} // namespace Trundle
