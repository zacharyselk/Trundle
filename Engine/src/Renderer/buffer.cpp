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
#include <Trundle/Core/log.h>
#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Platform/OpenGL/util.h>
#include <Trundle/Renderer/buffer.h>

namespace Trundle {

//===-- LayoutElement -----------------------------------------------------===//
LayoutElement::LayoutElement(Rendering::DataType type, const std::string& name,
                             uint32_t offset, bool normalize)
    : type(type), name(name), size(Rendering::getSize(type)),
      numberOfComponents(Rendering::numberOfComponents(type)), offset(offset),
      normalize(normalize) {}
//===----------------------------------------------------------------------===//

//===-- BufferLayout -----------------------------------------------------===//
BufferLayout::BufferLayout(std::initializer_list<LayoutElement> list)
    : stride(0) {
  layout.reserve(list.size());
  for (const auto& element : list) {
    layout.emplace_back(std::make_shared<LayoutElement>(element));
    stride += layout.back()->size;
  }
}

uint32_t BufferLayout::getStride() const { return stride; }

const Ref<LayoutElement> BufferLayout::operator[](size_t index) const {
  return layout[index];
}

size_t BufferLayout::size() const { return layout.size(); }

std::vector<Ref<LayoutElement>>::const_iterator BufferLayout::begin() const {
  return layout.begin();
}

std::vector<Ref<LayoutElement>>::const_iterator BufferLayout::end() const {
  return layout.end();
}
//===----------------------------------------------------------------------===//

//===-- IndexBuffer -------------------------------------------------------===//
Ref<IndexBuffer> IndexBuffer::create(const Ref<Renderer> renderer,
                                     std::vector<uint32_t> indices) {
  switch (renderer->getBackend()) {
  case RenderingBackend::OpenGL:
    return std::make_shared<OpenGL::IndexBuffer>(indices);
  default:
    Log::Error("TODO Unsupported index buffer backend");
  }

  return Ref<IndexBuffer>(nullptr);
}

IndexBuffer::~IndexBuffer() {}
//===----------------------------------------------------------------------===//

//===-- VertexBuffer ------------------------------------------------------===//
Ref<VertexBuffer> VertexBuffer::create(const Ref<Renderer> renderer,
                                       const std::vector<float> vertices,
                                       const Ref<BufferLayout> layout) {
  switch (renderer->getBackend()) {
  case RenderingBackend::OpenGL:
    return std::make_shared<OpenGL::VertexBuffer>(vertices, layout);
  default:
    Log::Error("TODO Unsupported index buffer backend");
  }

  return Ref<VertexBuffer>(nullptr);
}

VertexBuffer::~VertexBuffer() {}
//===----------------------------------------------------------------------===//

//===-- VertexArray -------------------------------------------------------===//
Ref<VertexArray>
VertexArray::create(const Ref<Renderer> renderer, Ref<IndexBuffer> indexBuffer,
                    std::vector<Ref<VertexBuffer>> vertexBuffers) {
  switch (renderer->getBackend()) {
  case RenderingBackend::OpenGL:
    return std::make_shared<OpenGL::VertexArray>(indexBuffer, vertexBuffers);
  default:
    Log::Error("TODO Unsupported index buffer backend");
  }

  return Ref<VertexArray>(nullptr);
}

VertexArray::~VertexArray() {}
//===----------------------------------------------------------------------===//

} // namespace Trundle