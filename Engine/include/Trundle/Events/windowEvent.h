#pragma once

#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>

namespace Trundle {

  class TRUNDLE_API WindowCloseEvent : public Event {
  public:
    EVENT_BOILERPLATE(WindowClose);
    WindowCloseEvent()  { }

    std::string toString() const override final {
      return std::string("Recieved WindowCloseEvent");
    }
  };

  class TRUNDLE_API WindowResizeEvent : public Event {
  public:
    EVENT_BOILERPLATE(WindowResize);
    WindowResizeEvent(int w, int h)
      : width(w), height(h)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved WindowResizeEvent with dimensions " << width
         << "x" << height;
      return ss.str();
    }

  private:
    int width{-1};
    int height{-1};  
  };

}
