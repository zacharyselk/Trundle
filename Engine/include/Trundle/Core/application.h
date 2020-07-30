#pragma once

#include <memory>

#include <Trundle/Core/core.h>
//#include <Trundle/Platform/MacOSWindow.h>
#include <Trundle/Core/window.h>

namespace Trundle {

    class TRUNDLE_API Application {
    public:
        Application();
        ~Application();

        void run();
        void onEvent(Event &event);

    private:
        std::unique_ptr<Window> window;
        bool running{true};
    };

    // Defined by the client code
    Application* CreateApplication();
};
