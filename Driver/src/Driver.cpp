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
#include <iostream>
#include <sstream>

class ExampleLayer : public Trundle::Layer {
public:
  ExampleLayer() : Layer("HelloLayer") {
    // Trundle::Shader shader(renderer, vs, fs);
    Trundle::Shader shader(renderer, "Driver/assets/basic.vs",
                           "Driver/assets/basic.fs");
    position.x = 0;
    position.y = 0;

    triangle.setWidth(1);
    triangle.setHeight(1);
    triangle.setShader(shader);
    triangle.set("color", glm::vec4(0.0, 1.0, 0.0, 1.0));
  }

  void onUpdate(Trundle::SceneRenderer& sceneRenderer) {
    position.x += 0.1 * Trundle::Time::deltaTime();
    triangle.setPosition(position.x, position.y);
    sceneRenderer.submit(triangle);
  }

  void onEvent(Trundle::Event& event) override final {
    Trundle::Log::Info(event.toString());
  }

private:
  Trundle::Triangle triangle;
  glm::vec3 position;
};

class Game : public Trundle::Application {
public:
  Game() { pushLayer(new ExampleLayer); }

  ~Game() {}
};

Trundle::Application* Trundle::CreateApplication() { return new Game(); }
