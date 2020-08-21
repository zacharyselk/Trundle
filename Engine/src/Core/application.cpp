//===-- application.cpp ----------------------------------------------------===//
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

#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/buffer.h>

//#include <GLFW/glfw3.h>


// Temporary
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <Trundle/Render/util.h>
#include <Trundle/Platform/OpenGL/util.h>

//#include <Trundle/Render/render.h>


namespace Trundle {

  // IndexBuffer* createIndexBuffer(OpenGLAPI, uint32_t* indices , uint32_t count) {
  //   IndexBuffer* buf = new IndexBuffer;
  //   glGenBuffers(1, &(buf->id));
  //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->id);
  //   glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

  //   return buf;
  // }



  // Temporary
  static unsigned int compileShader(unsigned int type, const std::string &src) {
    unsigned int id = glCreateShader(type);
    const char* c_src = src.c_str();
    glShaderSource(id, 1, &c_src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
      int len;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
      char* msg = new char[len];
      glGetShaderInfoLog(id, len, &len, msg);
      std::stringstream ss;
      ss << "Shader could not compile: " << msg;
      Log::Error(ss.str());
      exit(1);
    }

    return id;
  }

  // Temporary
  static unsigned int createShader(const std::string &vertexShader,
                                   const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
  }

  Application* Application::instance = nullptr;

    Application::Application() {
      instance = this;

      // Create window context and object. Window::create() also will initalize
      // the backend graphics api
      window = std::unique_ptr<Window>(Window::create());

      // Create the GUI layer that is placed on the render stack as a overlay
      // layer
      // TODO: Use shared pointer
      guiLayer = new ImGuiLayer;
      pushOverlay(guiLayer);

      // Bind onEvent to be called back from the window when it recieves an
      // event (ie. key press, mouse movement, etc)
      window->setEventCallback(std::bind(&Application::onEvent, this,
                                         std::placeholders::_1));

      // Temporary
      Renderer renderer(RenderingAPI::OpenGLAPI);

      glGenVertexArrays(1, &vertexArray);
      glBindVertexArray(vertexArray);


      // Triangle
      float vertices[7*3] = {
          -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
           0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
           0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
      };

      vertexBuffer = std::move(VertexBuffer(renderer, vertices, sizeof(vertices)));

      BufferLayout layout{
        { Trundle::Rendering::Float3, "position" },
        { Trundle::Rendering::Float4, "color"}
      };
      for (size_t i = 0; i < layout.size(); ++i) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
          i, layout[i].numberOfComponents, OpenGL::toOpenGL(Rendering::Float4), 
          layout[i].normalize ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)layout[i].offset);
      }

      unsigned int indices[3] = { 0, 1, 2 };
      indexBuffer = std::move(IndexBuffer(renderer, indices, 3));

      unsigned int vertexShader;
      vertexShader = glCreateShader(GL_VERTEX_SHADER);

      std::string vs =
        "#version 330 core\n"
        "layout(location = 0) in vec3 in_position;\n"
        "layout(location = 1) in vec4 in_color;\n"
        "out vec3 v_position;\n"
        "out vec4 v_color;\n"
        "void main(){\n"
        "  v_position = in_position;\n"
        "  v_color = in_color\n;"
        "  gl_Position = vec4(in_position, 1.0);\n"
        "}\n";
      std::string fs =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "in vec3 v_position;\n"
        "in vec4 v_color;\n"
        "void main(){\n"
        "  color = v_color*0.5 + vec4(v_position * 0.5 + 0.5, 1.0) * 0.5;\n"
        "}\n";

      unsigned int id = createShader(vs, fs);
      glUseProgram(id);

    }

    Application::~Application()  { }

    void Application::run() {
      while(running) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.54, 0.17, 0.89, 1);

        guiLayer->begin();
        for (Layer* layer : layerStack) {
          layer->onUpdate();
        }
        guiLayer->end();

        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        window->onUpdate();
        //GLFWwindow* w = static_cast<GLFWwindow*>(window->getNativeWindow());
        //glfwSwapBuffers(w);
      }
    }

    bool Application::onWindowClose(WindowCloseEvent &) {
      running = false;
      return true;
    }

  void Application::onEvent(Event &event) {
    EventDispatch dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

    for (auto it = layerStack.end(); it != layerStack.begin();) {
      --it;
      (*it)->onEvent(event);
      if (event.handled) {
        break;
      }
    }
  }

  void Application::pushLayer(Layer* layer) {
    layerStack.pushLayer(layer);
  }

  void Application::pushOverlay(Layer* overlay) {
    layerStack.pushOverlay(overlay);
  }

}
