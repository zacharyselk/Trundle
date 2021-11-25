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
std::shared_ptr<Shader> Shader::create(const Renderer& r, const std::string& vertexShader,
                      const std::string& fragmentShader) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::Shader>(vertexShader, fragmentShader);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

//===-- Uniform -----------------------------------------------------------===//
std::shared_ptr<Uniform> Uniform::create(const Renderer& r, const std::string& uniformName,
                 const uniform_t& uniformData) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    break;

  case RenderingAPI::OpenGLAPI:
    return std::make_shared<OpenGL::Uniform>(uniformName, uniformData);

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}
//===----------------------------------------------------------------------===//

} // namespace Trundle