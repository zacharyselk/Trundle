#pragma once

#include <Trundle/common.h>
#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>

namespace Trundle {

  class TRUNDLE_API MouseMoveEvent : public Event {
  public:
    EVENT_BOILERPLATE(MouseMove);
    MouseMoveEvent(double x, double y)
      : x(x), y(y)  { }

    std::tuple<int, int> getPos() const  { return std::make_tuple(x, y); }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MouseMoveEvent at position (" << x
         << ", " << y << ")";
      return ss.str();
    }

  private:
    double x = 0;
    double y = 0;
  };

  class TRUNDLE_API MouseButtonEvent : public Event {
  public:
    int getMouseCode() const  { return mouseCode; }

  protected:
    MouseButtonEvent(int mouseCode)
      : mouseCode(mouseCode)  { }

    int mouseCode{-1};
  };

  class TRUNDLE_API MousePressEvent : public MouseButtonEvent {
  public:
    EVENT_BOILERPLATE(MousePress);
    MousePressEvent(int mouseCode)
      : MouseButtonEvent(mouseCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MousePressEvent with mouseCode " << mouseCode;
      return ss.str();
    }
  };

  class TRUNDLE_API MouseReleaseEvent: public MouseButtonEvent {
  public:
    EVENT_BOILERPLATE(MouseRelease);
    MouseReleaseEvent(int mouseCode)
      : MouseButtonEvent(mouseCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MouseReleaseEvent with mouseCode " << mouseCode;
      return ss.str();
    }
  };

}
