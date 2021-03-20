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
#include <Trundle/Core/input.h>
#include <Trundle/Util/input.h>

// Temp
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle {

std::array<bool, 325> Input::keysDown{};
std::array<bool, 3> Input::mouseButtonsDown{};
double Input::mouseX = 0;
double Input::mouseY = 0;

bool Input::isKeyPressed(KeyCode keycode) {
  Application* app = Application::get();
  GLFWwindow* window =
      static_cast<GLFWwindow*>(app->getWindow()->getNativeWindow());
  int status = glfwGetKey(window, TrundleToGL(keycode));

  return status == GLFW_PRESS;
}

void Input::setKeyDown(KeyCode keycode) {
  keysDown[static_cast<int>(keycode)] = true;
}
void Input::setKeyUp(KeyCode keycode) {
  keysDown[static_cast<int>(keycode)] = false;
}

void Input::setMouseButtonDown(int buttonNum) {
  assert(buttonNum == 0 || buttonNum == 1 || buttonNum == 2 
         && "Not a mouse button");
  mouseButtonsDown[buttonNum] = true;
}

void Input::setMouseButtonUp(int buttonNum) {
  assert(buttonNum == 0 || buttonNum == 1 || buttonNum == 2 
         && "Not a mouse button");
  mouseButtonsDown[buttonNum] = false;
}

void Input::setMousePosition(double x, double y) {
  assert(x >= 0 && y >= 0 && "Invalid mouse position");
  mouseX = x;
  mouseY = y;
}

void Input::setMousePositionX(double x) {
  assert(x >= 0 && "Invalid mouse position");
  mouseX = x;
}

void Input::setMousePositionY(double y) {
  assert(y >= 0 && "Invalid mouse position");
  mouseY = y;
}

// TODO: Add some sort of keyup handling
void Input::handleKeysDown(std::function<void(KeyCode)> func) {
  for (size_t i = 0; i < keysDown.size(); ++i) {
    if (keysDown[i]) {
      if (!isKeyDown(static_cast<KeyCode>(i))) {
        keysDown[i] = false;
        continue;
      } else {
        func(static_cast<KeyCode>(i));
      }
    }
  }
}

bool Input::isKeyDown(KeyCode keycode) {
  return keysDown[static_cast<int>(keycode)];
}

bool Input::isKeyUp(KeyCode keycode) {
  return !keysDown[static_cast<int>(keycode)];
}

bool Input::isMouseButtonDown(int buttonNum) {
  assert(buttonNum == 0 || buttonNum == 1 || buttonNum == 2 
         && "Not a mouse button");
  return mouseButtonsDown[buttonNum];
}

bool Input::isMouseButtonUp(int buttonNum) {
  assert(buttonNum == 0 || buttonNum == 1 || buttonNum == 2 
         && "Not a mouse button");
  return !mouseButtonsDown[buttonNum];
}

std::tuple<double, double> Input::getMousePosition() {
  return {mouseX, mouseY};
}

double Input::getMousePositionX() {
  return mouseX;
}

double Input::getMousePositionY() {
  return mouseY;
}

} // namespace Trundle