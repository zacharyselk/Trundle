#pragma once


namespace Trundle {

  class RenderingContext {
  public:
    virtual bool init() = 0;
    virtual void swapBuffers() = 0;
  };

}
