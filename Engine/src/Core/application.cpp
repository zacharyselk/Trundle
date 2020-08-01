#include <functional>

#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>

#include <GLFW/glfw3.h>

namespace Trundle {

    Application::Application() {
      window = std::unique_ptr<Window>(Window::create());
      window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    Application::~Application()  { }

    void Application::run() {
      while(running) {
        glClearColor(0.54, 0.17, 0.89, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        window->onUpdate();
      }
    }

    bool Application::onWindowClose(WindowCloseEvent &) {
      running = false;
      return true;
    }

  void Application::onEvent(Event &event) {
    EventDispatch dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
  }
}
