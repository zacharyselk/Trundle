#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/keyEvent.h>

#include <GLFW/glfw3.h>


namespace Trundle {

    Application* Application::instance = nullptr;

    Application::Application() {
      instance = this;

      window = std::unique_ptr<Window>(Window::create());
      guiLayer = std::unique_ptr<ImGuiLayer>(new ImGuiLayer);
      window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    }

    Application::~Application()  { }

    void Application::run() {
      while(running) {
        glClearColor(0.54, 0.17, 0.89, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        guiLayer->begin();
        for (Layer* layer : layerStack) {
          layer->onUpdate();
        }
        guiLayer->end();

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
