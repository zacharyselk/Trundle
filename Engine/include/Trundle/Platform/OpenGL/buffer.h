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
// OpenGL implementation of the buffers rendering API.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/Render/buffer.h>


namespace Trundle::OpenGL {

  class IndexBuffer : public Trundle::IndexBuffer::IndexBufferConcept {
  public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~IndexBuffer();

  private:
    uint32_t id;
  };


  class VertexBuffer : public Trundle::VertexBuffer::VertexBufferConcept {
  public:
    VertexBuffer(float* vertices, uint32_t size);
    virtual ~VertexBuffer();

  private:
    uint32_t id;
  };
}
