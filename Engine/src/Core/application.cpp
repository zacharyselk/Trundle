//===-- application.cpp ---------------------------------------------------===//
//
// Copyright 2021 Zachary Selk
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
#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/windowEvent.h>
#include <Trundle/Util/input.h>

// Temp
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <Trundle/Renderer/render2D.h>

namespace Trundle {

Application* Application::instance = nullptr;

// Callback function used by the OpenGL interface to report warnings and errors
// to the console.
void GLAPIENTRY MessageCallback(GLenum /*source*/, GLenum type, GLuint /*id*/,
                                GLenum severity, GLsizei /*length*/,
                                const GLchar* message,
                                const void* /*userParam*/) {
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
    Log::Critical("Unknow OpenGL Severity Level!");
  }
  fprintf(stderr,
          "GL CALLBACK: %s\n  Type: 0x%x\n  Severity: %s\n  Message: %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
          severityStr.c_str(), message);
}

void openGLInit() {
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);
}

void clearColor(float r = 0.54, float g = 0.17, float b = 0.89, float a = 1) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, a);
}

Application::Application(bool runHeadless) : headless(runHeadless) {
  instance = this;

  // Create a new window object.
  if (!headless) {
    window = Ref<Window>(Window::create());
    window->setEventCallback([this](Event& e) { onEvent(e); });
  }
}

Application::~Application() {}

void Application::run() {
  openGLInit();
  while (running) {
    for (auto layer : layerStack) {
      layer->onUpdate();
    }

    if (!headless) {
      clearColor();
      Render2D::rect(-0.5, -0.5, 1, 1, Constant::Lime);
      Render2D::rect(-1, -1, 0.25, 0.25, Constant::Purple);
      Render2D::rect(0.75, 0.75, 0.25, 0.25, Constant::Gray);
      window->onUpdate();
    }
    // exit(1);
  }
}

void Application::run(Ref<Event> event) {
  // End early if the application is no longer running.
  if (!running) {
    return;
  }

  onEvent(*event);
  for (auto layer : layerStack) {
    layer->onUpdate();
  }

  if (!headless) {
    window->onUpdate();
  }
}

void Application::run(std::vector<Ref<Event>> events) {
  for (auto event : events) {
    run(event);
  }
}

bool Application::onKeyPress(KeyPressEvent& event) {
  // Convert the OpenGL keycode to a Trundle keycode then register it as being
  // pressed.
  Input::setKeyDown(GLToTrundle(event.getKeyCode()));
  return true;
}

bool Application::onKeyRelease(KeyReleaseEvent& event) {
  // Convert the OpenGL keycode to a Trundle keycode then register it as being
  // released.
  Input::setKeyUp(GLToTrundle(event.getKeyCode()));
  return true;
}

bool Application::onMousePress(MousePressEvent& event) {
  // Register the mouse press.
  Input::setMouseButtonDown(event.getMouseCode());
  return true;
}

bool Application::onMouseRelease(MouseReleaseEvent& event) {
  // Register the mouse release.
  Input::setMouseButtonUp(event.getMouseCode());
  return true;
}

bool Application::onMouseMove(MouseMoveEvent& event) {
  // Register the mouse move.
  auto [x, y] = event.getPosition();
  Input::setMousePosition(x, y);
  return true;
}

void Application::onEvent(Event& event) {
  EventDispatch dispatcher(event);
  dispatcher.dispatch<WindowCloseEvent>(
      [this](WindowCloseEvent& e) -> bool { return onWindowClose(e); });
  dispatcher.dispatch<KeyPressEvent>(
      [this](KeyPressEvent& e) -> bool { return onKeyPress(e); });
  dispatcher.dispatch<KeyReleaseEvent>(
      [this](KeyReleaseEvent& e) -> bool { return onKeyRelease(e); });
  dispatcher.dispatch<MousePressEvent>(
      [this](MousePressEvent& e) -> bool { return onMousePress(e); });
  dispatcher.dispatch<MouseReleaseEvent>(
      [this](MouseReleaseEvent& e) -> bool { return onMouseRelease(e); });
  dispatcher.dispatch<MouseMoveEvent>(
      [this](MouseMoveEvent& e) -> bool { return onMouseMove(e); });

  if (!event.handled) {
    for (auto it = layerStack.begin(); it != layerStack.end(); ++it) {
      (*it)->onEvent(event);
      if (event.handled) {
        break;
      }
    }

    if (!event.handled) {
      Log::Info(event.toString());
    }
  }
}

bool Application::onWindowClose(WindowCloseEvent& event) {
  running = false;
  event.handled = true;
  return true;
}

void Application::pushLayer(Ref<Layer> layer) { layerStack.pushLayer(layer); }

void Application::pushOverlay(Ref<Layer> overlay) {
  layerStack.pushOverlay(overlay);
}

void Application::popLayer(Ref<Layer> layer) { layerStack.popLayer(layer); }

void Application::popOverlay(Ref<Layer> overlay) {
  layerStack.popOverlay(overlay);
}

} // namespace Trundle