//===-- application.cpp ---------------------------------------------------===//
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
#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Core/time.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/renderingQueue.h>
#include <Trundle/Render/shader.h>
#include <Trundle/Util/input.h>
#include <Trundle/Util/primitives.h>

// Temp
#include <Trundle/Core/input.h>

namespace Trundle {

Application* Application::instance = nullptr;

Application::Application()
    : camera(0, 1280, 0, 720), renderer(RenderingAPI::OpenGLAPI) {
  instance = this;

  // Create window context and object. Window::create() also will initalize
  // the backend graphics api.
  window = std::unique_ptr<Window>(Window::create());

  // Create the GUI layer that is placed on the render stack as a overlay
  // layer.
  // TODO: Use shared pointer.
  //guiLayer = new ImGuiLayer;
  //pushOverlay(guiLayer);

  // Bind onEvent to be called back from the window when it recieves an
  // event (ie. key press, mouse movement, etc).
  window->setEventCallback(
      std::bind(&Application::onEvent, this, std::placeholders::_1));

  sceneRenderer = SceneRenderer::create(renderer);
}

Application::~Application() {}

void Application::run() {
  // std::function<void(KeyCode::Key)> handleKeyDown =
  //     std::bind(&Application::keyDown, this, std::placeholders::_1);
  while (running) {
    sceneRenderer.clear();
    sceneRenderer.start();

    //guiLayer->begin();
    for (Layer* layer : layerStack) {
      layer->onUpdate(sceneRenderer);
      layer->onImGuiRender();
    }
    //guiLayer->end();

    sceneRenderer.end();
    window->onUpdate();
  }
}

bool Application::onKeyPress(KeyPressEvent& event) {
  Input::setKeyDown(GLToTrundle(event.getKeyCode()));
  return true;
}

bool Application::onKeyRelease(KeyReleaseEvent& event) {
  Input::setKeyUp(GLToTrundle(event.getKeyCode()));
  return true;
}

bool Application::onWindowClose(WindowCloseEvent&) {
  running = false;
  return true;
}

void Application::onEvent(Event& event) {
  EventDispatch dispatcher(event);
  dispatcher.dispatch<WindowCloseEvent>(
      std::bind(&Application::onWindowClose, this, std::placeholders::_1));
  dispatcher.dispatch<KeyPressEvent>(
      std::bind(&Application::onKeyPress, this, std::placeholders::_1));
  dispatcher.dispatch<KeyReleaseEvent>(
      std::bind(&Application::onKeyRelease, this, std::placeholders::_1));

  for (auto it = layerStack.end(); it != layerStack.begin();) {
    --it;
    (*it)->onEvent(event);
    if (event.handled) {
      break;
    }
  }
}

void Application::pushLayer(Layer* layer) { layerStack.pushLayer(layer); }

void Application::pushOverlay(Layer* overlay) {
  layerStack.pushOverlay(overlay);
}

} // namespace Trundle
