//===-- input.cpp ---------------------------------------------------------===//
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
#include <Trundle/Core/input.h>
#include <Trundle/Core/keyCode.h>
#include <set>

TEST(Input, SetKeyDown) {
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  EXPECT_TRUE(Trundle::Input::isKeyDown(Trundle::KeyCode::A))
    << "Key setting did not work";

  // Cleanup
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  Trundle::Input::setKeyUp(Trundle::KeyCode::C);
}

TEST(Input, SetKeyUp) {
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  EXPECT_TRUE(Trundle::Input::isKeyUp(Trundle::KeyCode::A))
    << "Key release did not work";

  // Cleanup
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  Trundle::Input::setKeyUp(Trundle::KeyCode::C);
}

TEST(Input, SetMouseButtonDown) {
  Trundle::Input::setMouseButtonDown(0);
  EXPECT_TRUE(Trundle::Input::isMouseButtonDown(0))
    << "Mouse button setting did not work";

  // Cleanup
  Trundle::Input::setMouseButtonUp(0);
  Trundle::Input::setMouseButtonUp(1);
  Trundle::Input::setMouseButtonUp(2);
}

TEST(Input, SetMouseButtonUp) {
  Trundle::Input::setMouseButtonDown(1);
  Trundle::Input::setMouseButtonUp(1);
  EXPECT_TRUE(Trundle::Input::isMouseButtonUp(1))
    << "Mouse button release did not work";

  // Cleanup
  Trundle::Input::setMouseButtonUp(0);
  Trundle::Input::setMouseButtonUp(1);
  Trundle::Input::setMouseButtonUp(2);
}

TEST(Input, SetMousePosition) {
  Trundle::Input::setMousePosition(0.5, 1.0);
  auto [x, y] = Trundle::Input::getMousePosition();
  EXPECT_DOUBLE_EQ(0.5, x)
    << "Mouse x position is incorrect";
  EXPECT_DOUBLE_EQ(1.0, y)
    << "Mouse y position is incorrect";

  // Cleanup
  Trundle::Input::setMousePosition(0, 0);
}

TEST(Input, SetMousePositionX) {
  Trundle::Input::setMousePosition(0.5, 1.0);
  Trundle::Input::setMousePositionX(2.2);
  auto [x, y] = Trundle::Input::getMousePosition();
  EXPECT_DOUBLE_EQ(2.2, x)
    << "Mouse x position is incorrect";
  EXPECT_DOUBLE_EQ(1.0, y)
    << "Mouse y position is incorrect";
}

TEST(Input, SetMousePositionY) {
  Trundle::Input::setMousePosition(0.5, 1.0);
  Trundle::Input::setMousePositionY(2.1);
  auto [x, y] = Trundle::Input::getMousePosition();
  EXPECT_DOUBLE_EQ(0.5, x)
    << "Mouse x position is incorrect";
  EXPECT_DOUBLE_EQ(2.1, y)
    << "Mouse y position is incorrect";
}

TEST(Input, GetMousePositionX) {
  Trundle::Input::setMousePosition(0.5, 1.0);
  EXPECT_DOUBLE_EQ(0.5, Trundle::Input::getMousePositionX())
    << "Mouse x position is incorrect";
}

TEST(Input, GetMousePositionY) {
  Trundle::Input::setMousePosition(0.5, 1.0);
  EXPECT_DOUBLE_EQ(1.0, Trundle::Input::getMousePositionY())
    << "Mouse y position is incorrect";
}

TEST(Input, CheckDownKeys) {
  std::set<Trundle::KeyCode> keysDown;
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  Trundle::Input::setKeyDown(Trundle::KeyCode::B);
  Trundle::Input::setKeyDown(Trundle::KeyCode::C);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  std::function<void(Trundle::KeyCode)> lambda = [&](Trundle::KeyCode key) {
    keysDown.insert(key);
  };
  Trundle::Input::handleKeysDown(lambda);
  EXPECT_EQ(keysDown.size(), 2)
    << "There should be exactly 2 elements in the set";
  EXPECT_NE(keysDown.find(Trundle::KeyCode::A), keysDown.end())
    << "A was not pressed down";
  EXPECT_EQ(keysDown.find(Trundle::KeyCode::B), keysDown.end())
    << "B was not released";
  EXPECT_NE(keysDown.find(Trundle::KeyCode::C), keysDown.end())
    << "C was not pressed down";

  // Cleanup
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  Trundle::Input::setKeyUp(Trundle::KeyCode::C);
}

TEST(Input, MultiplePresses) {
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  Trundle::Input::setMouseButtonDown(2);
  Trundle::Input::setMouseButtonDown(2);
  EXPECT_TRUE(Trundle::Input::isKeyDown(Trundle::KeyCode::A))
    << "Key setting did not work";
  EXPECT_TRUE(Trundle::Input::isMouseButtonDown(2))
    << "Mouse button setting did not work";
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setMouseButtonUp(2);
  EXPECT_TRUE(Trundle::Input::isKeyUp(Trundle::KeyCode::A))
    << "Key release did not work";
  EXPECT_TRUE(Trundle::Input::isMouseButtonUp(2))
    << "Mouse button release did not work";

  // Cleanup
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  Trundle::Input::setKeyUp(Trundle::KeyCode::C);
  Trundle::Input::setMouseButtonUp(0);
  Trundle::Input::setMouseButtonUp(1);
  Trundle::Input::setMouseButtonUp(2);
}

TEST(Input, MultipleReleases) {
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setMouseButtonUp(0);
  Trundle::Input::setMouseButtonUp(0);
  EXPECT_TRUE(Trundle::Input::isKeyUp(Trundle::KeyCode::A))
    << "Key release did not work";
  EXPECT_TRUE(Trundle::Input::isMouseButtonUp(0))
    << "Mouse button release did not work";
  Trundle::Input::setKeyDown(Trundle::KeyCode::A);
  Trundle::Input::setMouseButtonDown(0);
  EXPECT_TRUE(Trundle::Input::isKeyDown(Trundle::KeyCode::A))
    << "Key setting did not work";
  EXPECT_TRUE(Trundle::Input::isMouseButtonDown(0))
    << "Mouse button setting did not work";

  // Cleanup
  Trundle::Input::setKeyUp(Trundle::KeyCode::A);
  Trundle::Input::setKeyUp(Trundle::KeyCode::B);
  Trundle::Input::setKeyUp(Trundle::KeyCode::C);
  Trundle::Input::setMouseButtonUp(0);
  Trundle::Input::setMouseButtonUp(1);
  Trundle::Input::setMouseButtonUp(2);
}