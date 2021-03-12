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
//
// Tests application in the engine.
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <gtest/gtest.h>
#include <memory>
#include <iostream>

class LayerA : public Trundle::Layer {
public:
  LayerA() : Layer("LayerA") {}
};

class Application : public Trundle::Application, public testing::Test {
public:
  Application()
   : Trundle::Application(HEADLESS) {}

  ~Application() {}

protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(Application, LayerPushing) {
  auto layer = std::make_shared<LayerA>();
  pushLayer(layer);
  ASSERT_TRUE(layerStack.begin() != layerStack.end()) 
    << "No new layer was added";
  ASSERT_TRUE(*layerStack.begin() == layer) 
    << "New layer is not at the top of the stack";
}

TEST_F(Application, OverlayPushing) {
  auto overlay = std::make_shared<LayerA>();
  pushOverlay(overlay);
  ASSERT_TRUE(layerStack.size() == 1) 
    << "No new overlay layer was added";
  ASSERT_TRUE(*layerStack.begin() == overlay) 
    << "New overlay layer is not at the top of the stack";
}

TEST_F(Application, LayerPoping) {
  auto layer1 = std::make_shared<LayerA>();
  auto layer2 = std::make_shared<LayerA>();

  pushLayer(layer1);
  pushLayer(layer2);
  ASSERT_TRUE(layerStack.size() == 2)
    << "Incorect number of layers in the stack";
  popLayer(layer2);
  auto stackTop = *layerStack.begin();
  ASSERT_TRUE(layer1 == stackTop)
    << "Bottom layer was removed";
  pushLayer(layer2);
  ASSERT_TRUE(layerStack.size() == 2)
    << "Layer was not re-added to the stack";
  popLayer(layer1);
  ASSERT_TRUE(layerStack.size() == 1)
    << "No layer was poped";
  stackTop = *layerStack.begin();
  ASSERT_TRUE(layer2 == stackTop)
    << "Top layer was removed";
}

TEST_F(Application, OverlayPoping) {
  auto overlay1 = std::make_shared<LayerA>();
  auto overlay2 = std::make_shared<LayerA>();

  pushOverlay(overlay1);
  pushOverlay(overlay2);
  ASSERT_TRUE(layerStack.size() == 2)
    << "Incorect number of layers in the stack";
  popOverlay(overlay2);
  auto stackTop = *layerStack.begin();
  ASSERT_TRUE(overlay1 == stackTop)
    << "Bottom overlay layer was removed";
  pushOverlay(overlay2);
  ASSERT_TRUE(layerStack.size() == 2)
    << "Overlay layer was not re-added to the stack";
  popOverlay(overlay1);
  ASSERT_TRUE(layerStack.size() == 1)
    << "No layer was poped";
  stackTop = *layerStack.begin();
  ASSERT_TRUE(overlay2 == stackTop)
    << "Top overlay layer was removed";
}