//===-- input.h -----------------------------------------------------------===//
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
// Input handling API.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>

// Temp
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <Trundle/Core/application.h>

namespace Trundle {

//===-- Input -------------------------------------------------------------===//
// A static singleton that manages which keys are currently pressed.
//===----------------------------------------------------------------------===//
class Input {
public:
  static bool isKeyPressed(int keycode);

  static void keyDown(int keycode);
  static void keyUp(int keycode);

  static void handleKeysDown(std::function<void(int)> func);

private:
  Input() = default;

  // TODO: Find and use the actual amount of keycodes
  static std::array<bool, 200> keysDown;
};

} // namespace Trundle