#pragma once

#include <Trundle/trundle.hpp>
#include <Trundle/Core/core.h>
#include <Trundle/Core/window.h>
#include <Trundle/Core/layer.h>
#include <Trundle/Core/layerStack.h>
#include <Trundle/Events/windowEvent.h>
#include <Trundle/Util/imGuiLayer.h>

namespace Trundle {

    class TRUNDLE_API Application {
    public:
      Application();
      ~Application();

      void run();
      void onEvent(Event &event);
      bool onWindowClose(WindowCloseEvent &);

      void pushLayer(Layer* layer);
      void pushOverlay(Layer* overlay);

      inline static Application* get()  { return instance; }
      inline Window& getWindow()  { return *window; }

    private:
      static Application* instance;
      std::unique_ptr<Window> window;
      std::unique_ptr<ImGuiLayer> guiLayer;
      bool running{true};

      LayerStack layerStack;
    };

    // Defined by the client code
    Application* CreateApplication();
};
