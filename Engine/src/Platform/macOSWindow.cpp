#if defined(TRUNDLE_OS_MACOS)

#include <sstream>

#include <Trundle/Platform/macOSWindow.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Events/mouseEvent.h>

namespace Trundle {

  static bool GLFWInitalized{false};

  Window* Window::create(const WindowProperties &properties) {
    return new MacOSWindow(properties);
  }

  MacOSWindow::MacOSWindow(const WindowProperties &properties) {
    init(properties);
  }

  MacOSWindow::~MacOSWindow() {
    shutdown();
  }

  void MacOSWindow::init(const WindowProperties &properties) {
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
      GLFWInitalized = true;
    }

    window = glfwCreateWindow(data.width, data.height, data.title.c_str(),
                              nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &data);
    setVSync(true);

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
  }

  void MacOSWindow::shutdown() {
    glfwDestroyWindow(window);
  }

  void MacOSWindow::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  void MacOSWindow::setVSync(bool enable) {
    if (enable) {
      glfwSwapInterval(1);
    } else {
      glfwSwapInterval(0);
    }
    data.vSync = enable;
  }

  bool MacOSWindow::isVSync() const {
    return data.vSync;
  }

}

#endif