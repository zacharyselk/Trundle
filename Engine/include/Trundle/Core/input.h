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
//
//===----------------------------------------------------------------------===//
class Input {
public:
  static bool isKeyPressed(int keycode) {
    Application* app = Application::get();
    GLFWwindow* window =
        static_cast<GLFWwindow*>(app->getWindow().getNativeWindow());
    int status = glfwGetKey(window, keycode);

    return status == GLFW_PRESS;
  }
};

} // namespace Trundle