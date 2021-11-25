//===-- openGLContext.cpp -------------------------------------------------===//
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
//===----------------------------------------------------------------------===//
#include <Trundle/Core/log.h>
#include <Trundle/Platform/OpenGL/openGLContext.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle {

#if defined(TRUNDLE_OS_WINDOWS) || defined(TRUNDLE_OS_LINUX)
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) {
  std::string severityStr;
  switch (severity) {
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    // No need to output anything on a notification
    return;

  case GL_DEBUG_SEVERITY_LOW:
    severityStr = "Low";
    break;

  case GL_DEBUG_SEVERITY_MEDIUM:
    severityStr = "Medium";
    break;

  case GL_DEBUG_SEVERITY_HIGH:
    severityStr = "High";
    break;

  default:
    Log::Error("Unknow OpenGL Severity Level!");
  }
  fprintf(stderr,
          "GL CALLBACK: %s\n  Type: 0x%x\n  Severity: %s\n  Message: %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
          severityStr.c_str(), message);
}
#endif

//===-- OpenGLContext -----------------------------------------------------===//
OpenGLContext::OpenGLContext(GLFWwindow* window) : windowHandle(window) {
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

  // DebugMessageCallback is not supported on MacOS
#if defined(TRUNDLE_OS_WINDOWS) || defined(TRUNDLE_OS_LINUX)
  // Enable debug output
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
#endif
  
  return true;
}

void OpenGLContext::swapBuffers() { glfwSwapBuffers(windowHandle); }

} // namespace Trundle
