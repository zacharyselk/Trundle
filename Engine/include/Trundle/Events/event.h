//===-- event.h ------------------------------------------------------------===//
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

// The base class for events. An event represents an interaction that the user
// has with the program, that includes keyboard events, mouse events, and
// actions performed to the window (ie resizing, closing, etc.).

#include <Trundle/common.h>
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
