#pragma once

#include <string>
#include <functional>

#include <Trundle/Events/event.h>


namespace Trundle {

  struct WindowProperties {
    std::string title;
    uint32_t width, height;
    bool vSync{false};

  WindowProperties(uint32_t w=1280, uint32_t h=720,
                   const std::string &str="Trundle")
    : title(str), width(w), height(h)  { }
  };


  class Window {
  public:
    using eventCallback = std::function<void(Event&)>;

    virtual ~Window()  { }

    virtual void onUpdate() = 0;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;

    virtual void setEventCallback(const eventCallback &callback) = 0;
    virtual void setVSync(bool enable) = 0;
    virtual bool isVSync() const = 0;

    static Window* create(const WindowProperties &properties=WindowProperties());
  };

}
