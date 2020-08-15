//===-- openGLContext.h ----------------------------------------------------===//
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
//===-----------------------------------------------------------------------===//

#pragma once

// Provides that OpenGL implementation of a graphical context and the API to
// use it

#include <Trundle/Render/renderingContext.h>

struct GLFWwindow;

namespace Trundle {

  class OpenGLContext : public RenderingContext {
  public:
    OpenGLContext(GLFWwindow* window);

    bool init() override final;
    void swapBuffers() override final;

  private:
    GLFWwindow* windowHandle;
  };

}
