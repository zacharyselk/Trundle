#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/log.h>
#include <Trundle/Render/renderer.h>
//#include <Trundle/Platform/OpenGL/buffer.h>


namespace Trundle {
namespace OpenGL {
  class IndexBuffer;
}

  class IndexBuffer {
  public:
    IndexBuffer(const Renderer &r, uint32_t* indices, uint32_t count);

    //create(const Renderer& r, uint32_t* indices, uint32_t size) const;
    friend class OpenGL::IndexBuffer;

  private:
    class IndexBufferConcept {
    public:
      virtual ~IndexBufferConcept() = default;
    };

    std::shared_ptr<IndexBufferConcept> vptr;
  };

}
