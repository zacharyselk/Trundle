#pragma once

#include <Trundle/Core/application.h>

#if defined(_WIN32)

extern Trundle::Application* Trundle::CreateApplication();

int main(int argc, char** argv) {
    Trundle::Log::Debug("Starting Engine\n");
    Trundle::Application* app = Trundle::CreateApplication();
    app->run();
    delete app;
    Trundle::Log::Debug("Application Closed\n");
}

#else

extern Trundle::Application* Trundle::CreateApplication();

int main(int argc, char** argv) {
  Trundle::Log::Debug("Starting the Engine");
  Trundle::Application* app = Trundle::CreateApplication();
  app->run();
  delete app;
  Trundle::Log::Debug("Application Closed");
}

#endif
