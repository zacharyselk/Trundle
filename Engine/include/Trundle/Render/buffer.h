//===-- buffer.h -----------------------------------------------------------===//
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
//===-----------------------------------------------------------------------===//
//
// Defines the buffer APIs for the backend.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/log.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/util.h>


namespace Trundle {

// Forward declare the backend implementations.
namespace OpenGL {
  class IndexBuffer;
  class VertexBuffer;
}

  //===-- LayoutElement ----------------------------------------------------===//
  //
  // A structure for defining how the layout of a vertex (element) is defined.
  // TODO: Possibly should be moved somewhere else, either into LayoutElement
  //       if it is the only one who uses this, otherwise maybe into
  //       Render/util.h
  //
  //===---------------------------------------------------------------------===//
  struct LayoutElement {
    LayoutElement(const Rendering::GraphicsType &type, const std::string &name, const bool &normalize=false);

    Rendering::GraphicsType type;
    std::string name;
    uint32_t elementSize;
    uint32_t numberOfComponents;
    uint32_t offset;
    bool normalize;
  };


  //===-- BufferLayout -----------------------------------------------------===//
  //
  // Constructs and calculates a genaric layout specification for a buffer.
  //
  //===---------------------------------------------------------------------===//
  class BufferLayout {
  public:
    BufferLayout(const std::initializer_list<LayoutElement> &layout);

    uint32_t getStride() const { return stride; }

    LayoutElement &operator[](size_t index);
    size_t size();
    std::vector<LayoutElement>::iterator begin();
    std::vector<LayoutElement>::iterator end();

  private:
    std::vector<LayoutElement> layout;
    uint32_t stride;
  };


  //===-- IndexBuffer ------------------------------------------------------===//
  //
  // API for the index buffer.
  //
  //===---------------------------------------------------------------------===//
  class IndexBuffer {
  public:
    IndexBuffer() = default;
    IndexBuffer(const Renderer &r, uint32_t* indices, uint32_t count);
    IndexBuffer(IndexBuffer&&) = default;
    IndexBuffer& operator=(const IndexBuffer &buf) noexcept
      { vptr = buf.vptr; return *this; }

    friend class OpenGL::IndexBuffer;

  private:
    // Virtual base class for polymorphism.
    class IndexBufferConcept {
    public:
      virtual ~IndexBufferConcept() = default;
    };

    // Custom virtual pointer to allow for value semantic polymorphism.
    std::shared_ptr<const IndexBufferConcept> vptr;
  };


  //===-- VertexBuffer -----------------------------------------------------===//
  //
  // API for the vertex buffer.
  //
  //===---------------------------------------------------------------------===//
  class VertexBuffer {
  public:
    VertexBuffer() = default;
    VertexBuffer(const Renderer &r, float* vertices, uint32_t size);
    VertexBuffer(VertexBuffer&&) = default;
    VertexBuffer& operator=(const VertexBuffer &buf) noexcept
      { vptr = buf.vptr; return *this; }

    //void setLayout(const BufferLayout &layout)  { vptr->setLayout(layout); }
    //const BufferLayout &getLayout()  { return vptr->getLayout(); }

    friend class OpenGL::VertexBuffer;

  private:
    // Virtual base class for polymorphism.
    class VertexBufferConcept {
    public:
      virtual ~VertexBufferConcept() = default;
    };

    // Custom virtual pointer to allow for value semantic polymorphism.
    std::shared_ptr<VertexBufferConcept> vptr;
  };

}
