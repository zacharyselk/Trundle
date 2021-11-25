//===-- pipeline.cpp ------------------------------------------------------===//
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
#include <Trundle/Platform/OpenGL/pipeline.h>

namespace Trundle::OpenGL {

Pipeline::Pipeline() { id = glCreateProgram(); }

Pipeline::~Pipeline() { glDeleteProgram(id); }

void Pipeline::addShader(const Ref<Trundle::Shader> shader) {
  glAttachShader(id, shader->getId());
}

void Pipeline::link() {
  glLinkProgram(id);

  int success;
  char infoLog[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    Log::Error("Shader Linking Failed:");
    Log::Error(infoLog);
  }
}

void Pipeline::bind() { glUseProgram(id); }

void Pipeline::setVec4f(std::string name, std::array<float, 4> data) {
  glUniform4f(glGetUniformLocation(id, name.c_str()), data[0], data[1], data[2],
              data[3]);
}

} // namespace Trundle::OpenGL