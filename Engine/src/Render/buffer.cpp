#include <Trundle/Platform/OpenGL/buffer.h>
#include <Trundle/Render/buffer.h>


namespace Trundle {

  IndexBuffer IndexBuffer::create(const Renderer& r,
                                  uint32_t* indices,
                                  uint32_t size) {
    switch (r.getAPI()) {
    case RenderingAPI::None:
      // TODO
      assert(false && "Headless rendering is not supported yet");
      break;

    case RenderingAPI::OpenGL:
      // TODO
      return OpenGL::IndexBuffer::create(r, indices, size);
    }
  }

}
