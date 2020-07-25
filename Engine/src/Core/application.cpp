#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>

namespace Trundle {

    Application::Application()  { }
    Application::~Application()  { }

    void Application::Run() {
      KeyPressEvent e(40, false);
      Log::Trace(e.toString());
      while(1);
    }
}
