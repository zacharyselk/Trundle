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
  guiLayer = new ImGuiLayer;
  pushOverlay(guiLayer);

  // Bind onEvent to be called back from the window when it recieves an
  // event (ie. key press, mouse movement, etc).
  window->setEventCallback(
      std::bind(&Application::onEvent, this, std::placeholders::_1));

  // Temporary.
  sceneRenderer = SceneRenderer::create(renderer);

  // Triangle.
  Triangle triangle(100, 50);
  triangle.setPosition(50, 50);
  unsigned int indices[3] = {0, 1, 2};
  // float vertices[7 * 3] = {-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  //                          0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  //                          0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
  float vertices[7 * 3] = {triangle.vertices[0][0],
                           triangle.vertices[0][1],
                           triangle.vertices[0][2],
                           1.0f,
                           1.0f,
                           0.0f,
                           1.0f,
                           triangle.vertices[1][0],
                           triangle.vertices[1][1],
                           triangle.vertices[1][2],
                           1.0f,
                           1.0f,
                           0.0f,
                           1.0f,
                           triangle.vertices[2][0],
                           triangle.vertices[2][1],
                           triangle.vertices[2][2],
                           1.0f,
                           1.0f,
                           0.0f,
                           1.0f};

  BufferLayout layout{{Trundle::Rendering::Float3, "position"},
                      {Trundle::Rendering::Float4, "color"}};

  VertexBuffer vertexBuffer(renderer, vertices, layout, sizeof(vertices));

  IndexBuffer indexBuffer(renderer, indices, 3);
  vertexArray = VertexArray::create(renderer, indexBuffer, vertexBuffer);

  // Square
  float squareVertices[4 * 7] = {0.0f,   0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                 100.0f, 0.0f,   0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                 0.0f,   100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

  auto squareVertexBuffer = VertexBuffer::create(
      renderer, squareVertices, layout, sizeof(squareVertices));
  std::vector<VertexBuffer> squareVertexBuffers = {squareVertexBuffer};

  auto squareIndexBuffer = std::move(IndexBuffer(renderer, squareIndices, 6));

  squareVertexArray =
      VertexArray::create(renderer, squareIndexBuffer, squareVertexBuffers);

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
  std::string colorVs = R"(
        #version 330 core
        layout(location = 0) in vec3 in_position;

        uniform mat4 viewProjection;
        uniform mat4 transform;
        uniform vec4 color;

        out vec3 v_position;
        out vec4 v_color;
        void main(){
          v_position = in_position;
          v_color = color;
          gl_Position = viewProjection * transform * vec4(in_position, 1.0);
        }
      )";
  std::string fs = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;
        void main(){
          //color = v_color*0.5 + vec4(v_position * 0.5 + 0.5, 1.0) * 0.5;
          color = v_color;
        }
      )";

  shader = Shader::create(renderer, vs, fs);
  colorShader = Shader::create(renderer, colorVs, fs);
}

Application::~Application() {}

void Application::run() {
  glm::mat4 trianglePos(1.0f);
  int count = 0;
  float speed = 200.0f;

  std::function<void(int)> handleKeyDown =
      std::bind(&Application::keyDown, this, std::placeholders::_1);

  while (running) {
    Input::handleKeysDown(handleKeyDown);
    sceneRenderer.clear();
    sceneRenderer.start();

    if (++count % 120 == 0) {
      speed *= -1;
    }
    trianglePos =
        glm::translate(trianglePos, glm::vec3(speed * Time::deltaTime(),
                                              speed * Time::deltaTime(), 0));
    Uniform projectionUniform(renderer, "viewProjection",
                              camera.getViewProjectionMatrix());
    Uniform translationUniform(renderer, "transform", trianglePos);

    guiLayer->begin();
    for (Layer* layer : layerStack) {
      layer->onUpdate();
    }
    guiLayer->end();

    if (++count % 60 == 0) {
      speed *= -1;
    }
    trianglePos =
        glm::translate(trianglePos, glm::vec3(speed * Time::deltaTime(),
                                              speed * Time::deltaTime(), 0));

    Uniform triangleTransform(renderer, "transform", trianglePos);
    Uniform projection(renderer, "viewProjection",
                       camera.getViewProjectionMatrix());

    Uniform blue(renderer, "color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        Uniform transform(
            renderer, "transform",
            glm::translate(glm::mat4(1.0f), glm::vec3(110 * i, 110 * j, 0.0f)));
        sceneRenderer.submit(vertexArray, colorShader,
                             {projection, transform, blue});
      }
    }

    sceneRenderer.submit(vertexArray, shader,
                         {projectionUniform, translationUniform});

    sceneRenderer.end();
    window->onUpdate();
  }
}

void Application::keyDown(int keycode) {
  glm::vec3 pos(0.0f, 0.0f, 0.0f);
  float movement = 300.0f * Time::deltaTime();

  switch (keycode) {
  case GLFW_KEY_W:
    pos.y = movement;
    break;

  case GLFW_KEY_A:
    pos.x = -movement;
    break;

  case GLFW_KEY_S:
    pos.y = -movement;
    break;

  case GLFW_KEY_D:
    pos.x = movement;
    break;

  default:
    return;
  }

  camera.setPosition(camera.getPosition() + pos);
  Uniform uniform(renderer, "viewProjection", camera.getViewProjectionMatrix());
  sceneRenderer.submit(vertexArray, shader, {uniform});
}

bool Application::onKeyPress(KeyPressEvent& event) {
  Input::keyDown(event.getKeyCode());

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
