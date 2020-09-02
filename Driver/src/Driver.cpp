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
  ExampleLayer() : Layer("HelloLayer") {}

  void onUpdate() override final {}

  void onEvent(Trundle::Event& event) override final {
    Trundle::Log::Info(event.toString());
  }
};

class Game : public Trundle::Application {
public:
  Game() { pushLayer(new ExampleLayer); }

  ~Game() {}
};

Trundle::Application* Trundle::CreateApplication() { return new Game(); }
