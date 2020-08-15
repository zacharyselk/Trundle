//===-- application.h ------------------------------------------------------===//
//
// Copyright 2020 Zachary Selk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===-----------------------------------------------------------------------===//

#pragma once

// The application class contains the main game loop logic for the engine

#include <Trundle/common.h>
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
