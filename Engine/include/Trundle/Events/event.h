#pragma once

#include <Trundle/Core/core.h>

namespace Trundle {

  enum class EventType {
    None=0,
    KeyPress, KeyRelease,
    MousePress, MouseRelease, MouseMove,
    WindowClose, WindowResize
  };

  enum class EventCategory {
    None=0,
    KeyEvent =   1 << 0,
    MouseEvent = 1 << 1
  };

  class TRUNDLE_API Event {
  public:
    virtual ~Event() = default;

    // Reflection
    virtual const char* getName() const = 0;
    virtual std::string getString() const { return getName(); }

    virtual EventType getEventType() const = 0;
    virtual std::string toString() const = 0;

    bool handled{false};

  protected:

    friend class EventDispatch;
  };


  class EventDispatch {
    template<typename T>
    using eventFunction = std::function<bool (T&)>;
  public:
    EventDispatch(Event& e)
      : event(e)  { }

    template<typename T>
    bool dispatch(eventFunction<T> func) {
      if (event.getEventType() == T::getStaticType()) {
        event.handled = func(*(T*) &event);
        return true;
      }

      return false;
    }

  private:
    Event &event;
  };


  // Logging function
  inline std::ostream& operator<<(std::ostream &os, Event &e) {
    return os << e.toString();
  }

}
