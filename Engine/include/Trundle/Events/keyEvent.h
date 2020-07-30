#pragma once

#include <string>
#include <sstream>

#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>


namespace Trundle {

  class TRUNDLE_API KeyEvent : public Event {
  public:
    int getKeyCode() const  { return keyCode; }

  protected:
    KeyEvent(int keyCode)
      : keyCode(keyCode)  { }

    int keyCode = -1;
  };


  class TRUNDLE_API KeyPressEvent : public KeyEvent {
  public:
    EVENT_BOILERPLATE(KeyPress);
    KeyPressEvent(int keyCode, bool repeatEvent)
      : KeyEvent(keyCode), repeatEvent(repeatEvent)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved KeyPressEvent with keyCode " << keyCode
         << " and is " << (repeatEvent ? "" : "not ") << "a repeated event";
      return ss.str();
    }

  private:
    bool repeatEvent = false;
  };


  class TRUNDLE_API KeyReleaseEvent: public KeyEvent {
  public:
    EVENT_BOILERPLATE(KeyRelease);
    KeyReleaseEvent(int keyCode)
      : KeyEvent(keyCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved KeyReleaseEvent with keyCode " << keyCode;
      return ss.str();
    }
  };

}
