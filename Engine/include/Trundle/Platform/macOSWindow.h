#pragma once

#include <Trundle/Core/window.h>
#include <Trundle/Render/renderingContext.h>

#include <GLFW/glfw3.h>

namespace Trundle {

  class MacOSWindow : public Window {
  public:
    using eventCallback = std::function<void(Event&)>;
    MacOSWindow(const WindowProperties &properties);
    virtual ~MacOSWindow();

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
