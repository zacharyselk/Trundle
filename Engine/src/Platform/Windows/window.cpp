//===-- window.cpp --------------------------------------------------------===//
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
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Events/mouseEvent.h>
#include <Trundle/Events/windowEvent.h>
#include <Trundle/Platform/Windows/window.h>

namespace Trundle {

// A static flag for keeping track of the status of GLFW.
static bool GLFWInitalized{false};

// Error callback for GLFW to print what error was thrown.
static void GLFWErrorCallback(int error, const char* description) {
  std::stringstream ss;
  ss << "GLFW Error " << error << ": " << description;
  Log::Error(ss.str());
  exit(1);
}

// Creates a new Windows window when create is called.
Window* Window::create(const WindowProperties& properties) {
  return new WindowsWindow(properties);
}

WindowsWindow::WindowsWindow(const WindowProperties& properties) {
  init(properties);
}

WindowsWindow::~WindowsWindow() { shutdown(); }

void WindowsWindow::init(const WindowProperties& properties) {
  // Copy settings from properties.
  data.title = properties.title;
  data.width = properties.width;
  data.height = properties.height;

  std::stringstream ss;
  ss << "Creating window " << properties.title << " with size "
     << properties.width << "x" << properties.height;
  Log::Trace(ss.str());

  // Try initalizing glfw if not done so already.
  // NOTE: Make sure this is handled properly when multi-threading.
  if (!GLFWInitalized) {
    int success = glfwInit();
    assert(success && "GLFW could not initalize a window");
    glfwSetErrorCallback(GLFWErrorCallback);
    GLFWInitalized = true;
  }

  // Must be compatible with OpenGL 3.3 core.
  // TODO: Change this when more backends are supported.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(data.width, data.height, data.title.c_str(),
                            nullptr, nullptr);

  glfwSetWindowUserPointer(window, &data);

  // Set callbacks from glfw.
  // TODO: Convert raw pointers to smart pointers.
  //       Add modifiers to events.
  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int /*scancode*/,
                                int action, int /*mods*/) {
    void* userPointer = glfwGetWindowUserPointer(window);
    WindowData* data = (WindowData*)userPointer;

    Event* event = nullptr;
    switch (action) {
    case GLFW_PRESS:
      event = new KeyPressEvent(key, false);
      break;

    case GLFW_REPEAT:
      event = new KeyPressEvent(key, true);
      break;

    case GLFW_RELEASE:
      event = new KeyReleaseEvent(key);
      break;

    default:
      assert(0 && "Unreachable");
    }

    data->callback(*event);
    delete event;
  });

  glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
    void* userPointer = glfwGetWindowUserPointer(window);
    WindowData* data = (WindowData*)userPointer;

    Event* event = new MouseMoveEvent(x, y);
    data->callback(*event);
    delete event;
  });

  glfwSetMouseButtonCallback(
      window, [](GLFWwindow* window, int button, int action, int /*mod*/) {
        void* userPointer = glfwGetWindowUserPointer(window);
        WindowData* data = (WindowData*)userPointer;

        Event* event = nullptr;
        switch (action) {
        case GLFW_PRESS:
          event = new MousePressEvent(button);
          break;

        case GLFW_RELEASE:
          event = new MouseReleaseEvent(button);
          break;

        default:
          assert(0 && "Unreachable");
        };

        data->callback(*event);
        delete event;
      });

  glfwSetWindowSizeCallback(
      window, [](GLFWwindow* window, int width, int height) {
        void* userPointer = glfwGetWindowUserPointer(window);
        WindowData* data = (WindowData*)userPointer;

        data->width = width;
        data->height = height;

        Event* event = new WindowResizeEvent(width, height);
        data->callback(*event);
        delete event;
      });

  glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
    void* userPointer = glfwGetWindowUserPointer(window);
    WindowData* data = (WindowData*)userPointer;

    Event* event = new WindowCloseEvent();
    data->callback(*event);
    delete event;
  });
}

void WindowsWindow::shutdown() { glfwDestroyWindow(window); }

void WindowsWindow::onUpdate() {
  // Check for events.
  //Log::Warn("Hello");
  glfwPollEvents();
  glfwSwapBuffers(window);
}

uint32_t WindowsWindow::getWidth() { 
  return data.width; 
}

uint32_t WindowsWindow::getHeight() { 
  return data.height; 
}

void WindowsWindow::setEventCallback(const EventCallback& cb) {
  data.callback = cb;
}

void WindowsWindow::setVSync(bool enable) {
  if (enable) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  data.vSync = enable;
}

bool WindowsWindow::isVSync() const { return data.vSync; }

void* WindowsWindow::getNativeWindow() const { return (void*)window; }

} // namespace Trundle