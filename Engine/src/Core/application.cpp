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

namespace Trundle {

Application* Application::instance = nullptr;

Application::Application() : camera() {
  instance = this;

  // Create window context and object. Window::create() also will initalize
  // the backend graphics api.
  window = std::unique_ptr<Window>(Window::create());

  // Create the GUI layer that is placed on the render stack as a overlay
  // layer.
  // TODO: Use shared pointer.
  guiLayer = new ImGuiLayer;
  pushOverlay(guiLayer);

  // Bind onEvent to be called back from the window when it recieves an
  // event (ie. key press, mouse movement, etc).
  window->setEventCallback(
      std::bind(&Application::onEvent, this, std::placeholders::_1));

  // Temporary.
  Renderer renderer(RenderingAPI::OpenGLAPI);
  // TODO: make this assignmnet better.
  sceneRenderer = std::move(SceneRenderer(renderer));

  // Triangle.
  unsigned int indices[3] = {0, 1, 2};
  float vertices[7 * 3] = {-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                           0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

  BufferLayout layout{{Trundle::Rendering::Float3, "position"},
                      {Trundle::Rendering::Float4, "color"}};

  // TODO: make this assignmnet better.
  auto vertexBuffer =
      std::move(VertexBuffer(renderer, vertices, layout, sizeof(vertices)));
  std::vector<VertexBuffer> vertexBuffers = {vertexBuffer};

  auto indexBuffer = std::move(IndexBuffer(renderer, indices, 3));

  // TODO: make this assignmnet better.
  vertexArray = std::move(VertexArray(renderer, vertexBuffers, indexBuffer));

  std::string vs = R"(
        #version 330 core
        layout(location = 0) in vec3 in_position;
        layout(location = 1) in vec4 in_color;

        uniform mat4 viewProjection;
        uniform mat4 transform;

        out vec3 v_position;
        out vec4 v_color;
        void main(){
          v_position = in_position;
          v_color = in_color;
          gl_Position = viewProjection * transform * vec4(in_position, 1.0);
        }
      )";
  std::string fs = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;
        void main(){
          color = v_color*0.5 + vec4(v_position * 0.5 + 0.5, 1.0) * 0.5;
        }
        )";

  Uniform uniform("viewProjection", camera.getViewProjectionMatrix());

  // TODO: make this assignmnet better.
  shader = std::move(Shader(renderer, vs, fs, uniform));
  shader.bind();
}

Application::~Application() {}

void Application::run() {
  glm::mat4 trianglePos(1.0f);
  int count = 0;
  float increment = 1.5f;
  while (running) {
    sceneRenderer.clear();
    sceneRenderer.start();

    // camera.setPosition(camera.getPosition() + (glm::vec3{0.01f} *
    // sceneRenderer.deltaTime()));
    // camera.setRotation(camera.getRotation() +
    //                    10.0f * Time::deltaTime());
    if (count % 120 == 0) {
      increment *= -1;
    }
    count += increment / 1.5f + 0.0001;
    trianglePos = glm::translate(
        trianglePos, glm::vec3(increment * Time::deltaTime(),
                               increment * Time::deltaTime(), 0));
    Uniform projectionUniform("viewProjection",
                              camera.getViewProjectionMatrix());
    Uniform translationUniform("transform", trianglePos);
    std::vector<Uniform> uniforms = {projectionUniform, translationUniform};
    shader.reset(uniforms);

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

bool Application::onWindowClose(WindowCloseEvent&) {
  running = false;
  return true;
}

void Application::onEvent(Event& event) {
  EventDispatch dispatcher(event);
  dispatcher.dispatch<WindowCloseEvent>(
      std::bind(&Application::onWindowClose, this, std::placeholders::_1));

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
