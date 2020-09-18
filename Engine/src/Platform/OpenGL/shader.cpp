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
#include <Trundle/Util/common.h>
#include <Trundle/Util/file.h>

//#include <type_traits>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

namespace Trundle::OpenGL {

//===-- Shader ------------------------------------------------------------===//
Shader::Shader(const std::string& vertexShader,
               const std::string& fragmentShader)
    : id(glCreateProgram()) {
  uint32_t vs, fs;

  // Compile the vertex shader.
  if (Trundle::isFilePath(vertexShader)) {
    vs = compile(GL_VERTEX_SHADER, Trundle::readFile(vertexShader));
  } else {
    vs = compile(GL_VERTEX_SHADER, vertexShader);
  }

  // Compile the fragment shader.
  if (Trundle::isFilePath(fragmentShader)) {
    fs = compile(GL_FRAGMENT_SHADER, Trundle::readFile(fragmentShader));
  } else {
    fs = compile(GL_FRAGMENT_SHADER, fragmentShader);
  }

  glAttachShader(id, vs);
  glAttachShader(id, fs);
  glLinkProgram(id);
  glValidateProgram(id);

  glDeleteShader(vs);
  glDeleteShader(fs);

  bind();
}

Shader::~Shader() { glDeleteProgram(id); }

std::shared_ptr<const Trundle::Shader::ShaderConcept> Shader::move() const {
  std::shared_ptr<const Trundle::Shader::ShaderConcept> copy =
      std::make_shared<const Shader>(*this);

  // Set id to 0 to invalidate the object
  const_cast<std::remove_const<decltype(id)>::type&>(id) = 0;

  return copy;
}

void Shader::bind() const { glUseProgram(id); }

void Shader::unbind() const { glUseProgram(0); }

uint32_t Shader::getId() const { return id; }

uint32_t Shader::compile(unsigned int type, const std::string& src) {
  unsigned int srcId = glCreateShader(type);
  const char* c_src = src.c_str();
  glShaderSource(srcId, 1, &c_src, NULL);
  glCompileShader(srcId);

  int result;
  glGetShaderiv(srcId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int len;
    glGetShaderiv(srcId, GL_INFO_LOG_LENGTH, &len);
    char* msg = new char[len];
    glGetShaderInfoLog(srcId, len, &len, msg);
    std::stringstream ss;
    ss << "Shader could not compile: " << msg;
    Log::Error(ss.str());
    exit(1);
  }

  return srcId;
}
//===----------------------------------------------------------------------===//

//===-- Uniform -----------------------------------------------------------===//
Uniform::Uniform(const std::string& uniformName, const uniform_t& uniformData)
    : name(uniformName), data(uniformData) {}

// TODO: Implement
Uniform::~Uniform() {}

void Uniform::bind(uint32_t shaderId) const {
  GLint loc = glGetUniformLocation(shaderId, name.c_str());
  assert(loc != -1 && "Error: Uniform location not found!");
  std::visit(
      common::visitors{
          [&](const glm::vec3& uniform) {
            glUniform3f(loc, uniform.x, uniform.y, uniform.z);
          },
          [&](const glm::vec4& uniform) {
            glUniform4f(loc, uniform.x, uniform.y, uniform.z, uniform.w);
          },
          [&](const glm::mat4& uniform) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(uniform));
          },
      },
      data);
}

// TODO: Not sure if this should be implemented or just removed because unforms
//       automatically become unbound when a program is unbound.
void Uniform::unbind() const {}
//===----------------------------------------------------------------------===//

} // namespace Trundle::OpenGL