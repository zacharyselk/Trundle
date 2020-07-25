#pragma once

#include <Trundle/Events/event.h>
#include <tuple>

namespace Trundle {

  class TRUNDLE_API MouseMovedEvent : Event {
  public:
    MouseEvent(float x, float y)
      : x(x), y(y)  { }

    int getPos() const  { return {x, y}; }

  private:
    float x = 0;
    flaot y = 0;
  };

  class TRUNDLE_API MouseButtonEvent : Event {
  public:
    int getMouseCode() const  { return mouseCode; }

  protected:
    MouseButtonEvent(int mouseCode)
      : mouseCode(mouseCode)  { }

    int mouseCode = -1;
  };

  class TRUNDLE_API MouseDownEvent : MouseButtonEvent {};
  class TRUNDLE_API MouseUpEvent: MouseButtonEvent {};

}
