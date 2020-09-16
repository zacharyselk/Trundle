//===-- imGuiLayer.h ------------------------------------------------------===//
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
//
// A simple example of a user-end driver, used to test the code.
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <sstream>

class ExampleLayer : public Trundle::Layer {
public:
  const std::string vs = R"(
        #version 330 core
        layout(location = 0) in vec3 position;

        uniform mat4 viewProjection;
        uniform vec4 color;

        out vec3 v_position;
        out vec4 v_color;
        void main(){
          v_position = position;
          v_color = color;
          gl_Position = viewProjection * vec4(position, 1.0);
        }
      )";
  const std::string fs = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;
        void main(){
          //color = v_color*0.5 + vec4(v_position * 0.5 + 0.5, 1.0) * 0.5;
          color = v_color;
        }
      )";

  ExampleLayer() : Layer("HelloLayer") {
    Trundle::Shader shader(renderer, vs, fs);
    position.x = 0;
    position.y = 0;

    triangle.setWidth(1);
    triangle.setHeight(1);
    triangle.setShader(shader);
    triangle.set("position", position);
    triangle.set("color", glm::vec4(0.0, 1.0, 0.0, 1.0));
  }

  void onUpdate() override final {
    sceneRenderer.clear();
    sceneRenderer.start();

    position.x += 0.01 * Trundle::Time::deltaTime();
    triangle.set("position", position);
    sceneRenderer.submit(triangle);

    sceneRenderer.end();
  }

  void onEvent(Trundle::Event& event) override final {
    Trundle::Log::Info(event.toString());
  }

private:
  Trundle::Triangle triangle;
  // Trundle::Coord2d<float> position;
  glm::vec4 position;
};

class Game : public Trundle::Application {
public:
  Game() { pushLayer(new ExampleLayer); }

  ~Game() {}
};

Trundle::Application* Trundle::CreateApplication() { return new Game(); }
