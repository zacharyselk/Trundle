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
  class VertexArray;
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
    LayoutElement(const uint32_t &osffset, const Rendering::GraphicsType &type, const std::string &name, const bool &normalize=false);
    //LayoutElement(const uint32_t &offset, const std::initializer_list<LayoutElement> &lst)
    //  : LayoutElement(std::forward<std::initializer_list<LayoutElement>>(lst))  { }
    LayoutElement(const LayoutElement &element) = default;

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
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<LayoutElement> &layout);
    BufferLayout(const BufferLayout &layout) = default;
    BufferLayout(BufferLayout&&) noexcept = default;
    BufferLayout& operator=(const BufferLayout &layout) noexcept
      { this->layout = layout.layout; this->stride = layout.stride; return *this; }

    uint32_t getStride() const { return stride; }

    const std::shared_ptr<LayoutElement> &operator[](size_t index) const;
    size_t size();
    std::vector<std::shared_ptr<LayoutElement>>::const_iterator begin() const;
    std::vector<std::shared_ptr<LayoutElement>>::const_iterator end() const;

  private:
    // TODO: Make const
    std::vector<std::shared_ptr<LayoutElement>> layout;
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
    //IndexBuffer(IndexBuffer&&) = default;
    IndexBuffer& operator=(const IndexBuffer &buf) noexcept
      { vptr = buf.vptr; return *this; }

    void bind() const { vptr->bind(); }
    void unbind() const { vptr->unbind(); }

    friend class OpenGL::IndexBuffer;

  private:
    // Virtual base class for polymorphism.
    class IndexBufferConcept {
    public:
      virtual ~IndexBufferConcept() = default;

      virtual void bind() const = 0;
      virtual void unbind() const = 0;
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
    VertexBuffer(const Renderer &r, float* vertices, 
                 const BufferLayout &layout, uint32_t size);
    //VertexBuffer(VertexBuffer&&) = default;
    VertexBuffer& operator=(const VertexBuffer &buf) noexcept
      { vptr = buf.vptr; return *this; }

    const BufferLayout &getLayout() const  { return vptr->getLayout(); }

    void bind() const { vptr->bind(); }
    void unbind() const { vptr->unbind(); }

    friend class OpenGL::VertexBuffer;

  private:
    // Virtual base class for polymorphism.
    class VertexBufferConcept {
    public:
      virtual ~VertexBufferConcept() = default;

      virtual void bind() const = 0;
      virtual void unbind() const = 0;
      virtual const BufferLayout &getLayout() const = 0;
    };

    // Custom virtual pointer to allow for value semantic polymorphism.
    std::shared_ptr<const VertexBufferConcept> vptr;
  };


  //===-- VertexArray ------------------------------------------------------===//
  //
  // API for the vertex array.
  //
  //===---------------------------------------------------------------------===//
  class VertexArray {
  public:
    VertexArray() = default;
    // TODO: We only need to pass around the buffer vptrs
    VertexArray(const Renderer &r, 
                const std::vector<VertexBuffer> &vertexBuffers,
                const std::vector<IndexBuffer> &indexBuffers);
    VertexArray(VertexArray&&) = default;
    VertexArray(const VertexArray &array)
      { vptr = array.vptr; }
    VertexArray& operator=(const VertexArray &array) noexcept
      { vptr = array.vptr; return *this; }

    void bind() const { vptr->bind(); }
    void unbind() const { vptr->unbind(); }

    friend class OpenGL::VertexArray;

  private:
    // Virtual base class for polymorphism.
    class VertexArrayConcept {
    public:
      virtual ~VertexArrayConcept() = default;

      virtual void bind() const = 0;
      virtual void unbind() const = 0;
    };

    // Custom virtual pointer to allow for value semantic polymorphism.
    std::shared_ptr<const VertexArrayConcept> vptr;
  };

}
