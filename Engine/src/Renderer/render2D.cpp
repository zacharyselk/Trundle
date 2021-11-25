//===-- render2D.cpp ------------------------------------------------------===//
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
#include <Trundle/Renderer/buffer.h>
#include <Trundle/Renderer/pipeline.h>
#include <Trundle/Renderer/render2D.h>
#include <Trundle/Renderer/shader.h>
#include <glm/gtc/type_ptr.hpp>

// Temp
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace Trundle {

void Render2D::quad(const Ref<glm::mat4> /*transform*/) {}

static const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "uniform vec4 objectColor;\n"
                                          "void main() {\n"
                                          "  FragColor = objectColor;\n"
                                          "}\0";

void Render2D::rect(float x, float y, float w, float h, const Color& c) {
  static std::vector<uint32_t> ib = {0, 1, 3, 1, 2, 3};
  std::vector<float> points = {x + w, y + h, 0, x + w, y,     0,
                               x,     y,     0, x,     y + h, 0};
  auto pos = std::make_shared<std::vector<float>>(points);
  auto renderer = std::make_shared<Renderer>(RenderingBackend::OpenGL);
  BufferLayout l = {{Rendering::DataType::Float3, "pos"}};
  auto layout = std::make_shared<BufferLayout>(l);
  auto vertexBuffer = VertexBuffer::create(renderer, points, layout);
  auto indexBuffer = IndexBuffer::create(renderer, ib);
  auto vertexArray = VertexArray::create(renderer, indexBuffer, {vertexBuffer});
  auto vertexShader = Shader::create(renderer, ShaderType::VertexShader);
  auto fragmentShader = Shader::create(renderer, ShaderType::FragmentShader);
  auto pipeline = Pipeline::create(renderer);
  vertexShader->loadString(vertexShaderSource);
  fragmentShader->loadString(fragmentShaderSource);
  pipeline->addShader(vertexShader);
  pipeline->addShader(fragmentShader);
  pipeline->link();

  pipeline->bind();
  auto [r, g, b, a] = c.normalize();
  pipeline->setVec4f("objectColor", {r, g, b, a});
  vertexArray->bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

} // namespace Trundle