#if defined(TRUNDLE_OS_WINDOWS)

#include <sstream>
#include <cassert>

#include <Trundle/Platform/windowsWindow.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Events/mouseEvent.h>
#include <Trundle/Events/windowEvent.h>

namespace Trundle {

  static bool GLFWInitalized{false};

  static void GLFWErrorCallback(int error, const char* description)
	{
    std::stringstream ss;
    ss << "GLFW Error " << error << ": " << description;
    Log::Error(ss.str());
	}

  Window* Window::create(const WindowProperties &properties) {
    return new WindowsWindow(properties);
  }

  WindowsWindow::WindowsWindow(const WindowProperties &properties) {
    init(properties);
  }

  WindowsWindow::~WindowsWindow() {
    shutdown();
  }

  void WindowsWindow::init(const WindowProperties &properties) {
    data.title = properties.title;
    data.width = properties.width;
    data.height = properties.height;

    // TODO: log needs a formatting option
    std::stringstream ss;
    ss << "Creating window " << properties.title << " with size "
       << properties.width << "x" << properties.height;
    Log::Trace(ss.str());

    if (!GLFWInitalized) {
      int success = glfwInit();
      assert(success && "GLFW could not initalize a window");
      glfwSetErrorCallback(GLFWErrorCallback);
      GLFWInitalized = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(data.width, data.height, data.title.c_str(),
                              nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &data);
    setVSync(true);

    if (gl3wInit()) {
      printf("failed to initialize OpenGL\n");
      exit(1);
    }

    // Set callbacks from glfw
    // TODO: Convert raw pointers to smart pointers
    //       Add modifiers to events
    glfwSetKeyCallback(window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
          void* userPointer = glfwGetWindowUserPointer(window);
          WindowData* data = (WindowData *)userPointer;

          std::stringstream ss;
          ss << "Key is: " << key;
          Log::Debug(ss.str());

          Event* event;
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

    glfwSetCursorPosCallback(window,
        [](GLFWwindow* window, double x, double y) {
          void* userPointer = glfwGetWindowUserPointer(window);
          WindowData* data = (WindowData *)userPointer;

          Event* event = new MouseMoveEvent(x, y);
          data->callback(*event);
          delete event;
        });

    glfwSetMouseButtonCallback(window,
        [](GLFWwindow* window, int button, int action, int mod) {
          void* userPointer = glfwGetWindowUserPointer(window);
          WindowData* data = (WindowData *)userPointer;

          Event* event;

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

    glfwSetWindowSizeCallback(window,
        [](GLFWwindow* window, int width, int height) {
          void* userPointer = glfwGetWindowUserPointer(window);
          WindowData* data = (WindowData *)userPointer;

          data->width = width;
          data->height = height;

          Event* event = new WindowResizeEvent(width, height);
          data->callback(*event);
          delete event;
        });

    glfwSetWindowCloseCallback(window,
        [](GLFWwindow* window) {
          void* userPointer = glfwGetWindowUserPointer(window);
          WindowData* data = (WindowData *)userPointer;

          //window->shutdown();

          Event* event = new WindowCloseEvent();
          data->callback(*event);
          delete event;
        });
  }

  void WindowsWindow::shutdown() {
    glfwDestroyWindow(window);
  }

  void WindowsWindow::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  void WindowsWindow::setVSync(bool enable) {
    if (enable) {
      glfwSwapInterval(1);
    } else {
      glfwSwapInterval(0);
    }
    data.vSync = enable;
  }

  bool WindowsWindow::isVSync() const {
    return data.vSync;
  }

  void* WindowsWindow::getNativeWindow() const {
    return (void*)window;
  }

}

#endif
