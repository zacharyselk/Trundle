//===-- driver.cpp --------------------------------------------------------===//
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
//
// A sample driver for the engine
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <memory>
#include <iostream>

class LayerA : public Trundle::Layer {
public:
  LayerA() : Layer("LayerA") {}
};

class Application : public Trundle::Application {
public:
  Application()
   : Trundle::Application() { pushLayer(std::make_shared<LayerA>()); }

  ~Application() {}
};

Trundle::Application* Trundle::CreateApplication(int* /*argc*/, char** /*argv*/,
                                                 char** /*argp*/) {
  return new Application();
}