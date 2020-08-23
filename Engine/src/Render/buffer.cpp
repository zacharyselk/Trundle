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

#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/util.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle {

  //===-- LayoutElement ----------------------------------------------------===//
  LayoutElement::LayoutElement(const Rendering::GraphicsType &type, const std::string &name, const bool &normalize)
    : type(type), name(name), elementSize(Rendering::getSizeOf(type)), 
    numberOfComponents(elementSize/Rendering::getComponentSizeOf(type)), 
    offset(-1), normalize(normalize)  { }


  //===-- BufferLayout -----------------------------------------------------===//
  BufferLayout::BufferLayout(const std::initializer_list<LayoutElement> &layout)
    : layout(layout), stride(0) {
    for (auto& element : this->layout) {
      element.offset = stride;
      stride += element.elementSize;
    }
  }

  LayoutElement &BufferLayout::operator[](size_t index) {
    return layout[index];
  }

  size_t BufferLayout::size() {
    return layout.size();
  }

  std::vector<LayoutElement>::iterator BufferLayout::begin()  { 
    return layout.begin(); 
  }

  std::vector<LayoutElement>::iterator BufferLayout::end()  { 
    return layout.end(); 
  }


  //===-- IndexBuffer ------------------------------------------------------===//
  IndexBuffer::IndexBuffer(const Renderer &r, uint32_t* indices, uint32_t count) 
    : vptr(nullptr) {
    switch (r.getAPI()) {
      // TODO: Implement
      case RenderingAPI::None:
        break;

      case RenderingAPI::OpenGLAPI:
        vptr = std::make_shared<OpenGL::IndexBuffer>(indices, count);
        break;

      default:
        Log::Error("Unknown graphics API");
        exit(1);
    }
  }


  //===-- VertexBuffer -----------------------------------------------------===//
  VertexBuffer::VertexBuffer(const Renderer &r, float* vertices, uint32_t size) 
    : vptr(nullptr) {
    switch (r.getAPI()) {
      // TODO: Implement
      case RenderingAPI::None:
        break;

      case RenderingAPI::OpenGLAPI:
        vptr = std::make_shared<OpenGL::VertexBuffer>(vertices, size);
        break;

      default:
        Log::Error("Unknown graphics API");
        exit(1);
    }
  }


  //===-- VertexArray ------------------------------------------------------===//
    VertexArray::VertexArray(const Renderer &r) 
    : vptr(nullptr) {
    switch (r.getAPI()) {
      // TODO: Implement
      case RenderingAPI::None:
        break;

      case RenderingAPI::OpenGLAPI:
        vptr = std::make_shared<OpenGL::VertexArray>();
        break;

      default:
        Log::Error("Unknown graphics API");
        exit(1);
    }
  }

  
}
