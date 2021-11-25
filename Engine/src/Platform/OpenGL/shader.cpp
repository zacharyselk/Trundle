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
#include <GL/gl3w.h>
#include <Trundle/Core/log.h>
#include <Trundle/Platform/OpenGL/shader.h>
#include <Trundle/Util/file.h>

namespace Trundle::OpenGL {

Shader::Shader(Trundle::ShaderType type) : type(type) {
  switch (type) {
  case Trundle::ShaderType::None:
    Log::Error("Attempting to create a shader of type 'None'");
    break;
  case Trundle::ShaderType::VertexShader:
    id = glCreateShader(GL_VERTEX_SHADER);
    break;
  case Trundle::ShaderType::FragmentShader:
    id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  case Trundle::ShaderType::ComputeShader:
    Log::Error("TODO Compute shaders not implemented for OpenGL yet");
    break;
  }
}

Shader::~Shader() { glDeleteShader(id); }

void Shader::loadString(const std::string& shader) {
  source = shader.c_str();
  glShaderSource(id, 1, &source, NULL);
  compile();
}

void Shader::loadFile(const std::string& filename) {
  File file(filename);
  loadString(file.read());
}

void Shader::compile() {
  glCompileShader(id);

  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    Log::Error("Shader Compilation Failed:");
    Log::Error(infoLog);
  }
}

Trundle::ShaderType Shader::getType() { return type; }

uint32_t Shader::getId() { return id; }

} // namespace Trundle::OpenGL