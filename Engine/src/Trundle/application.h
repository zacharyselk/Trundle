#pragma once

#include "core.h"

namespace Trundle {

    class TRUNDLE_API Application {
        public:
        Application();
        ~Application();

        void Run();
    };

    // Defined by the client code
    Application* CreateApplication();
};