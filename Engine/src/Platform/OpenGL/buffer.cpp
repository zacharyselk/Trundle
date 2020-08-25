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
#include <Trundle/Platform/OpenGL/util.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle::OpenGL {

    //===-- IndexBuffer ----------------------------------------------------===//
    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), 
                     indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    //===-- VertexBuffer ---------------------------------------------------===//
    VertexBuffer::VertexBuffer(
        float* vertices, const BufferLayout &layout, uint32_t size) 
        : layout(layout) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &id);
    }

    const BufferLayout &VertexBuffer::getLayout() const {
        return layout;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    //===-- VertexArray ----------------------------------------------------===//
    VertexArray::VertexArray(
        const std::vector<Trundle::VertexBuffer> &vertexBuffers,
        const std::vector<Trundle::IndexBuffer> &indexBuffers) 
        : vertexBuffers(vertexBuffers), indexBuffers(indexBuffers) {
        // OpenGL 4.5
        //glCreateVertexArrays(1, &id);

        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        for (const auto &buf : vertexBuffers) {
            buf.bind();

            BufferLayout layout = buf.getLayout();
            for (size_t i = 0; i < layout.size(); ++i) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
            i, layout[i]->numberOfComponents, OpenGL::toOpenGL(layout[i]->type), 
            layout[i]->normalize ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)layout[i]->offset);
            }
        }

        for (const auto &buf : indexBuffers) {
            buf.bind();
        }
    }

    VertexArray::~VertexArray() {
        glDeleteBuffers(1, &id);
    }

    void VertexArray::bind() const {
        glBindVertexArray(id);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

}