//===-- buffer.cpp ---------------------------------------------------------===//
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

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle::OpenGL {

    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) {
        Log::Debug("IndexBuffer ctor");
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), 
                     indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        Log::Debug("IndexBuffer dtor");
        glDeleteBuffers(1, &id);
    }


    VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
        Log::Debug("VertexBuffer ctor");
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        Log::Debug("VertexBuffer dtor");
        glDeleteBuffers(1, &id);
    }

}