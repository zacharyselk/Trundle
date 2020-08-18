#include <Trundle/Platform/OpenGL/buffer.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle::OpenGL {

    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), 
                     indices, GL_STATIC_DRAW);
        Log::Debug("Called IndexBuffer Constructor");
    }

}