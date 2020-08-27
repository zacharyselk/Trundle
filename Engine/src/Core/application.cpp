//===-- application.cpp ----------------------------------------------------===//
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
//===-----------------------------------------------------------------------===//

#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/shader.h>
#include <Trundle/Render/renderingQueue.h>


namespace Trundle {

  Application* Application::instance = nullptr;

    Application::Application() {
      instance = this;

      // Create window context and object. Window::create() also will initalize
      // the backend graphics api
      window = std::unique_ptr<Window>(Window::create());

      // Create the GUI layer that is placed on the render stack as a overlay
      // layer
      // TODO: Use shared pointer
      guiLayer = new ImGuiLayer;
      pushOverlay(guiLayer);

      // Bind onEvent to be called back from the window when it recieves an
      // event (ie. key press, mouse movement, etc)
      window->setEventCallback(std::bind(&Application::onEvent, this,
                                         std::placeholders::_1));

      Renderer renderer(RenderingAPI::OpenGLAPI);
      sceneRenderer = std::move(SceneRenderer(renderer));

      // Triangle
      unsigned int indices[3] = { 0, 1, 2 };
      float vertices[7*3] = {
          -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
           0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
           0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
      };

      BufferLayout layout{
        { Trundle::Rendering::Float3, "position" },
        { Trundle::Rendering::Float4, "color"}
      };

      auto vertexBuffer = std::move(VertexBuffer(renderer, vertices, layout, sizeof(vertices)));
      std::vector<VertexBuffer> vertexBuffers = { vertexBuffer };

      auto indexBuffer = std::move(IndexBuffer(renderer, indices, 3));

      vertexArray = std::move(VertexArray(renderer, vertexBuffers, indexBuffer));

      std::string vs =
        "#version 330 core\n"
        "layout(location = 0) in vec3 in_position;\n"
        "layout(location = 1) in vec4 in_color;\n"
        "out vec3 v_position;\n"
        "out vec4 v_color;\n"
        "void main(){\n"
        "  v_position = in_position;\n"
        "  v_color = in_color\n;"
        "  gl_Position = vec4(in_position, 1.0);\n"
        "}\n";
      std::string fs =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "in vec3 v_position;\n"
        "in vec4 v_color;\n"
        "void main(){\n"
        "  color = v_color*0.5 + vec4(v_position * 0.5 + 0.5, 1.0) * 0.5;\n"
        "}\n";

      shader = std::move(Shader(renderer, vs, fs));
      shader.bind();

    }

    Application::~Application()  { }

    void Application::run() {
      while(running) {
        sceneRenderer.clear();

        sceneRenderer.start();

        guiLayer->begin();
        for (Layer* layer : layerStack) {
          layer->onUpdate();
        }
        guiLayer->end();

        sceneRenderer.submit(vertexArray);
        sceneRenderer.end();

        window->onUpdate();
      }
    }

    bool Application::onWindowClose(WindowCloseEvent &) {
      running = false;
      return true;
    }

  void Application::onEvent(Event &event) {
    EventDispatch dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

    for (auto it = layerStack.end(); it != layerStack.begin();) {
      --it;
      (*it)->onEvent(event);
      if (event.handled) {
        break;
      }
    }
  }

  void Application::pushLayer(Layer* layer) {
    layerStack.pushLayer(layer);
  }

  void Application::pushOverlay(Layer* overlay) {
    layerStack.pushOverlay(overlay);
  }

}
