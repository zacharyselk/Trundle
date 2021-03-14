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
#include <memory>
#include <iostream>

class LayerA : public Trundle::Layer {
public:
  LayerA() : Layer("LayerA") {}

  virtual void onAttach() override { onAttachCalled = true; }
  virtual void onDetach() override { onDetachCalled = true; }
  virtual void onUpdate() override { onUpdateCalled = true; }
  virtual void onEvent(Trundle::Event&) override { 
    onEventCalled = true;
  }

  bool onAttachCalled{false};
  bool onDetachCalled{false};
  bool onUpdateCalled{false};
  bool onEventCalled{false};
};

class Layers : public Trundle::Application, public testing::Test {
public:
  Layers()
   : Trundle::Application(HEADLESS) {}

  ~Layers() {}

protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(Layers, OnAttach) {
  auto layer = std::make_shared<LayerA>();
  auto overlay = std::make_shared<LayerA>();

  pushLayer(layer);
  EXPECT_TRUE(layer->onAttachCalled) 
    << "onAttach() was not called for layer";
  pushOverlay(overlay);
  EXPECT_TRUE(overlay->onAttachCalled) 
    << "onAttach() was not called for overlay";
}

TEST_F(Layers, OnDetach) {
  auto layer = std::make_shared<LayerA>();
  auto overlay = std::make_shared<LayerA>();

  pushLayer(layer);
  popLayer(layer);
  EXPECT_TRUE(layer->onDetachCalled) 
    << "onDetach() was not called for layer";
  pushOverlay(overlay);
  popOverlay(overlay);
  EXPECT_TRUE(overlay->onDetachCalled) 
    << "onDetach() was not called for overlay";
}

TEST_F(Layers, OnUpdate) {
  auto layer = std::make_shared<LayerA>();
  auto overlay = std::make_shared<LayerA>();
  auto event = std::make_shared<Trundle::MouseMoveEvent>(1,1);

  pushLayer(layer);
  run(event);
  EXPECT_TRUE(layer->onUpdateCalled) 
    << "onUpdate() was not called for layer";
  popLayer(layer);
  

  pushOverlay(overlay);
  run(event);
  EXPECT_TRUE(overlay->onUpdateCalled) 
    << "onUpdate() was not called for overlay";
  popOverlay(overlay);
}

TEST_F(Layers, OnEvent) {
  auto layer = std::make_shared<LayerA>();
  auto overlay = std::make_shared<LayerA>();
  auto event = std::make_shared<Trundle::MouseMoveEvent>(1,1);

  pushLayer(layer);
  run(event);
  EXPECT_TRUE(layer->onEventCalled) 
    << "onEvent() was not called for layer";
  popLayer(layer);
  

  pushOverlay(overlay);
  run(event);
  EXPECT_TRUE(overlay->onEventCalled) 
    << "onEvent() was not called for overlay";
  popOverlay(overlay);
}

TEST_F(Layers, GetName) {
  auto layer = std::make_shared<LayerA>();
  EXPECT_EQ(std::string("LayerA"), layer->getName())
    << "Layer name was miss labeled";
}