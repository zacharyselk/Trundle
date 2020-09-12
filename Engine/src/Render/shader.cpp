//===-- shader.cpp --------------------------------------------------------===//
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
#include <Trundle/Platform/OpenGL/shader.h>
#include <Trundle/Render/shader.h>

namespace Trundle {

//===-- Shader ------------------------------------------------------------===//
Shader::Shader(const Renderer& r, const std::string& vertexShader,
               const std::string& fragmentShader)
    : vptr(nullptr) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    break;

  case RenderingAPI::OpenGLAPI:
    vptr = std::make_shared<OpenGL::Shader>(vertexShader, fragmentShader);
    break;

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

//===-- Uniform -----------------------------------------------------------===//
Uniform::Uniform(const Renderer& r, const std::string& uniformName,
                 const uniform_t& uniformData)
    : vptr(nullptr) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    break;

  case RenderingAPI::OpenGLAPI:
    vptr = std::make_shared<OpenGL::Uniform>(uniformName, uniformData);
    break;

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

} // namespace Trundle