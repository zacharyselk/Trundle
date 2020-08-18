#pragma once

#include <Trundle/Render/buffer.h>


namespace Trundle::OpenGL {

  class IndexBuffer : public Trundle::IndexBuffer::IndexBufferConcept {
  public:
    IndexBuffer(uint32_t* indices, uint32_t count);

  private:
    uint32_t id;
  };

}
