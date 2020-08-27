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
//
// The application class is a singlton that contains the main game loop for the
// engine.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/core.h>
#include <Trundle/Core/window.h>
#include <Trundle/Core/layer.h>
#include <Trundle/Core/layerStack.h>
#include <Trundle/Events/windowEvent.h>
#include <Trundle/Util/imGuiLayer.h>
#include <Trundle/Render/buffer.h>
#include <Trundle/Render/shader.h>
#include <Trundle/Render/renderingQueue.h>


namespace Trundle {

    class TRUNDLE_API Application {
    public:
      Application();
      ~Application();

      // The main game loop
      void run();

      // Handles what to do when the window is closed.
      bool onWindowClose(WindowCloseEvent &);

      // Despatch the apropriot function corrisponding which event what recived.
      void onEvent(Event &event);

      // An interface for pushing layers to the layerstack for the application
      // to proccess every tick.
      void pushLayer(Layer* layer);
      void pushOverlay(Layer* overlay);

      // Returns a pointer to the singleton instance of the class.
      inline static Application* get()  { return instance; }

      // Returns a pointer to the window.
      inline Window& getWindow()  { return *window; }

    private:
      static Application* instance;

      LayerStack layerStack;
      bool running{true};

      std::unique_ptr<Window> window;
      //std::unique_ptr<ImGuiLayer> guiLayer;
      ImGuiLayer* guiLayer;

      //unsigned int vertexBuffer, indexBuffer;
      //unsigned int vertexArray;

      //std::shared_ptr<VertexBuffer> vertexBuffer;
      VertexArray vertexArray;
      Shader shader;
      SceneRenderer sceneRenderer;
      //std::shared_ptr<IndexBuffer> indexBuffer;
    };

    // Defined by the driver as an entry point into the engine.
    Application* CreateApplication();
};
