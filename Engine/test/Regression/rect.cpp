//===-- layer.cpp --------------------------------------------------------===//
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
// Tests layers in the engine.
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

using namespace Trundle;

class LayerA : public Layer {
public:
  LayerA() : Layer("LayerA") {}

  virtual void onAttach() override {
    r = std::make_shared<Rect>(1.0, 5.0, Color::Blue);
  }

  virtual void onDetach() override {}
  virtual void onUpdate() override {}
  virtual void onEvent(Event&) override {}

  Ref<Rect> r;
};

class Rectangle : public Application, public testing::Test {
public:
  Application() : Trundle::Application(HEADLESS) { pushLayer(std::make_shared<LayerA>();
  }

  ~Application() {}

protected:
  void SetUp() override {}
  void TearDown() override {}
};