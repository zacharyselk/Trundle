//===-- windowsWindow.h ----------------------------------------------------===//
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

// The Windows implementation of creating a repersentation for a window

#include <Trundle/Core/window.h>
#include <Trundle/Render/renderingContext.h>

#include <GLFW/glfw3.h>

namespace Trundle {

  class WindowsWindow : public Window {
  public:
    using eventCallback = std::function<void(Event&)>;
    WindowsWindow(const WindowProperties &properties);
    virtual ~WindowsWindow();

    void onUpdate() override final;
    uint32_t getWidth() override final  { return data.width; }
    uint32_t getHeight() override final  { return data.height; }

    void setEventCallback(const eventCallback &callback) override final {
      data.callback = callback;
    }
    void setVSync(bool enable) override final;
		bool isVSync() const override final;

    void* getNativeWindow() const override final;

    //virtual Window getWindow() const  { return window; }

  private:
    virtual void init(const WindowProperties &properties);
    virtual void shutdown();

    struct WindowData {
      std::string title;
      uint32_t width, height;
      bool vSync;

      eventCallback callback;
    };

    WindowData data;
    RenderingContext* context;
    GLFWwindow* window;
  };

}
