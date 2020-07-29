#include <sstream>

#include <Trundle/Platform/macOSWindow.h>
#include <Trundle/Core/log.h>

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
