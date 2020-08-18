#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Render/buffer.h>


namespace Trundle {

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
      }
  }

}
