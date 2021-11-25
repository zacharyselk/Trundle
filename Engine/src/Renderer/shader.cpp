//===-- shader.cpp --------------------------------------------------------===//
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
#include <Trundle/Core/log.h>
#include <Trundle/Platform/OpenGL/shader.h>
#include <Trundle/Renderer/shader.h>
#include <Trundle/Util/file.h>

namespace Trundle {

Ref<Shader> Shader::create(const Ref<Renderer> renderer, ShaderType type) {
  switch (renderer->getBackend()) {
  case RenderingBackend::OpenGL:
    return std::make_shared<OpenGL::Shader>(type);
  default:
    Log::Error("TODO Unsupported shader type");
  }

  return Ref<Shader>(nullptr);
}

Shader::~Shader() {}

} // namespace Trundle