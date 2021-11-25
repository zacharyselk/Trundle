//===-- events.cpp --------------------------------------------------------===//
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
// Tests events in the engine.
//
//===----------------------------------------------------------------------===//
#include <Trundle.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Hard coding keycode.
int GLFW_KEY_A = 65;

class Events : public Trundle::Application, public testing::Test {
public:
  Events() : Trundle::Application(HEADLESS) {}

  ~Events() {}

protected:
  void SetUp() override {}
  void TearDown() override {}
};

//===-- Key Events -----------------------------------------------------===//
TEST_F(Events, KeyPressEvent) {
  auto event = std::make_shared<Trundle::KeyPressEvent>(GLFW_KEY_A, 0);
  run(event);
  ASSERT_TRUE(event->handled) << "KeyPressEvent was not handled";
}

TEST_F(Events, KeyReleaseEvent) {
  auto event = std::make_shared<Trundle::KeyReleaseEvent>(GLFW_KEY_A);
  run(event);
  ASSERT_TRUE(event->handled) << "KeyReleaseEvent was not handled";
}
//===----------------------------------------------------------------------===//

//===-- Mouse Events -----------------------------------------------------===//
TEST_F(Events, MousePressEvent) {
  auto event = std::make_shared<Trundle::MousePressEvent>(1);
  run(event);
  ASSERT_TRUE(event->handled) << "MousePressEvent was not handled";
}

TEST_F(Events, MouseReleaseEvent) {
  auto event = std::make_shared<Trundle::MouseReleaseEvent>(1);
  run(event);
  ASSERT_TRUE(event->handled) << "MouseReleaseEvent was not handled";
}

TEST_F(Events, MouseMoveEvent) {
  auto event = std::make_shared<Trundle::MouseMoveEvent>(10, 10);
  run(event);
  ASSERT_TRUE(event->handled) << "MouseMoveEvent was not handled";
}
//===----------------------------------------------------------------------===//

//===-- Window Events -----------------------------------------------------===//
TEST_F(Events, WindowCloseEvent) {
  auto event = std::make_shared<Trundle::WindowCloseEvent>();
  run(event);
  ASSERT_TRUE(event->handled) << "WindowCloseEvent was not handled";
}

TEST_F(Events, DISABLED_WindowResizeEvent) {
  auto event = std::make_shared<Trundle::WindowResizeEvent>(10, 10);
  run(event);
  ASSERT_TRUE(event->handled) << "WindowResizeEvent was not handled";
}
//===----------------------------------------------------------------------===//