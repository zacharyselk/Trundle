//===-- input.cpp ---------------------------------------------------------===//
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
#include <Trundle/Core/input.h>
#include <Trundle/Util/input.h>

// Temp
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle {

std::array<bool, 400> Input::keysDown{};

bool Input::isKeyPressed(KeyCode::Key keycode) {
  Application* app = Application::get();
  GLFWwindow* window =
      static_cast<GLFWwindow*>(app->getWindow().getNativeWindow());
  int status = glfwGetKey(window, TrundleToGL(keycode));

  return status == GLFW_PRESS;
}

void Input::setKeyDown(KeyCode::Key keycode) {
  keysDown[static_cast<int>(keycode)] = true;
}
void Input::setKeyUp(KeyCode::Key keycode) {
  keysDown[static_cast<int>(keycode)] = false;
}

// TODO: Add some sort of keyup handling
void Input::handleKeysDown(std::function<void(KeyCode::Key)> func) {
  for (size_t i = 0; i < keysDown.size(); ++i) {
    if (keysDown[i]) {
      if (!isKeyPressed(static_cast<KeyCode::Key>(i))) {
        keysDown[i] = false;
        continue;
      } else {
        func(static_cast<KeyCode::Key>(i));
      }
    }
  }
}

bool Input::isKeyDown(KeyCode::Key keycode) {
  return keysDown[static_cast<int>(keycode)];
}

bool Input::isKeyUp(KeyCode::Key keycode) {
  return !keysDown[static_cast<int>(keycode)];
}

} // namespace Trundle