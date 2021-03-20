//===-- layerStack.cpp ----------------------------------------------------===//
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
#include <gtest/gtest.h>
#include <Trundle/Core/layerStack.h>

TEST(LayerStack, DefaultConstructor) {
  Trundle::LayerStack stack;
  stack.size();
  EXPECT_EQ(0u, stack.size())
    << "Stack should be empty when initalized";
}

TEST(LayerStack, PushLayer) {
  Trundle::LayerStack stack;
  auto layer = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer);
  EXPECT_EQ(1u, stack.size())
    << "Stack should contain exactly 1 layer";
  EXPECT_EQ(layer, *stack.begin());
}

TEST(LayerStack, PopLayer) {
  Trundle::LayerStack stack;
  auto layer = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer);
  stack.popLayer(layer);
  EXPECT_EQ(0u, stack.size())
    << "Stack should contain no layers after pop";
}

TEST(LayerStack, PushOverlay) {
  Trundle::LayerStack stack;
  auto overlay = std::make_shared<Trundle::Layer>();
  stack.pushOverlay(overlay);
  EXPECT_EQ(1u, stack.size())
    << "Stach should have exactly 1 layer";
}

TEST(LayerStack, PopOverlay) {
  Trundle::LayerStack stack;
  auto overlay = std::make_shared<Trundle::Layer>();
  stack.pushOverlay(overlay);
  stack.popOverlay(overlay);
  EXPECT_EQ(0u, stack.size())
    << "Stack should contain no layers after pop";
}

TEST(LayerStack, PopNonExistingLayer) {
  Trundle::LayerStack stack;
  auto layer1 = std::make_shared<Trundle::Layer>();
  auto layer2 = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer1);
  stack.popLayer(layer2);
  EXPECT_EQ(1u, stack.size())
    << "Invalid pop should not have removed any layers";
}

TEST(LayerStack, PopNonExistingOverlay) {
  Trundle::LayerStack stack;
  auto overlay1 = std::make_shared<Trundle::Layer>();
  auto overlay2 = std::make_shared<Trundle::Layer>();
  stack.pushOverlay(overlay1);
  stack.popOverlay(overlay2);
  EXPECT_EQ(1u, stack.size())
    << "Invalid pop should not have removed any layers";
}

TEST(LayerStack, Begin) {
  Trundle::LayerStack stack;
  auto layer1 = std::make_shared<Trundle::Layer>();
  auto layer2 = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer2);
  stack.pushLayer(layer1);
  EXPECT_EQ(layer1.get(), stack.begin()->get())
    << "Top of the stack is not correct";
  EXPECT_NE(layer2.get(), stack.begin()->get())
    << "Layers are in the wrong order";
  EXPECT_EQ(layer2.get(), (stack.begin()+1)->get())
    << "Bottom of the stack is not correct";
}

TEST(LayerStack, End) {
  Trundle::LayerStack stack;
  auto layer1 = std::make_shared<Trundle::Layer>();
  auto layer2 = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer2);
  stack.pushLayer(layer1);
  EXPECT_EQ(layer2, *(stack.end()-1))
    << "Bottom of the stack is not correct";
  EXPECT_EQ(layer1, *(stack.end()-2))
    << "Top of the stack is not correct";
}

TEST(LayerStack, LoopThroughLayers) {
  Trundle::LayerStack stack;
  auto layer1 = std::make_shared<Trundle::Layer>();
  auto layer2 = std::make_shared<Trundle::Layer>();
  size_t count = 0;
  ASSERT_EQ(stack.begin(), stack.end())
    << "begin iterator and end iterator should be equal in an empty stack";
  stack.pushLayer(layer1);
  stack.pushLayer(layer2);
  ASSERT_NE(stack.begin(), stack.end())
    << "begin iterator and end iterator should not be equal in a non-empty stack";
  ASSERT_EQ(stack.begin()+2, stack.end())
    << "begin iterator and end iterator should have a distance of 2";
  for (auto it = stack.begin(); it != stack.end(); ++it, ++count);
  EXPECT_EQ(2u, count)
    << "Iterators did not iterate over all the elements";
}

TEST(LayerStack, LayerOrdering) {
  Trundle::LayerStack stack;
  auto layer1 = std::make_shared<Trundle::Layer>();
  auto layer2 = std::make_shared<Trundle::Layer>();
  auto layer3 = std::make_shared<Trundle::Layer>();
  auto overlay1 = std::make_shared<Trundle::Layer>();
  auto overlay2 = std::make_shared<Trundle::Layer>();
  auto overlay3 = std::make_shared<Trundle::Layer>();
  stack.pushLayer(layer1);
  stack.pushOverlay(overlay1);
  stack.pushLayer(layer2);
  stack.pushLayer(layer3);
  stack.pushOverlay(overlay2);
  stack.pushOverlay(overlay3);
  EXPECT_EQ(overlay3, *stack.begin())
    << "Incorrect first element from the begining";
  EXPECT_EQ(overlay2, *(stack.begin()+1))
    << "Incorrect second element from the begining";
  EXPECT_EQ(overlay1, *(stack.begin()+2))
    << "Incorrect third element from the begining";
  EXPECT_EQ(layer3, *(stack.begin()+3))
    << "Incorrect fourth element from the begining";
  EXPECT_EQ(layer2, *(stack.begin()+4))
    << "Incorrect fifth element from the begining";
  EXPECT_EQ(layer1, *(stack.begin()+5))
    << "Incorrect sixth element from the begining";
  EXPECT_EQ(layer1, *(stack.end()-1))
    << "Incorrect first element from the end";
  EXPECT_EQ(layer2, *(stack.end()-2))
    << "Incorrect second element from the end";
  EXPECT_EQ(layer3, *(stack.end()-3))
    << "Incorrect third element from the end";
  EXPECT_EQ(overlay1, *(stack.end()-4))
    << "Incorrect fourth element from the end";
  EXPECT_EQ(overlay2, *(stack.end()-5))
    << "Incorrect fifth element from the end";
  EXPECT_EQ(overlay3, *(stack.end()-6))
    << "Incorrect sixth element from the end";
}