#include <Trundle/Core/log.h>
#include <Trundle/Platform/OpenGL/openGLContext.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle {

  OpenGLContext::OpenGLContext(GLFWwindow* window)
    : windowHandle(window) {
    assert(window && "Error: Window handler is uninitalized");
  }

  bool OpenGLContext::init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(windowHandle);
    if (gl3wInit()) {
      Log::Error("failed to initialize OpenGL\n");
      return false;
    }

    return true;
  }

  void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(windowHandle);
  }

}
