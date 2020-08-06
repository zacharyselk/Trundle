#pragma once

#include <Trundle/Render/renderingContext.h>

struct GLFWwindow;

namespace Trundle {

  class OpenGLContext : public RenderingContext {
  public:
    OpenGLContext(GLFWwindow* window);

    bool init() override final;
    void swapBuffers() override final;

  private:
    GLFWwindow* windowHandle;
  };

}
