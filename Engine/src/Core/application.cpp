#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>

namespace Trundle {

    Application::Application() {
      window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application()  { }

    void Application::Run() {
      while(1) {
        window->onUpdate();
      }
    }
}
