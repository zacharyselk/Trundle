//===-- event.h -----------------------------------------------------------===//
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
//===----------------------------------------------------------------------===//
//
// The base class for events. An event represents an interaction that the user
// has with the program, that includes keyboard events, mouse events, and
// actions performed to the window (ie resizing, closing, etc.).
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/core.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- EventType ---------------------------------------------------------===//
// All of the types of events in the Engine.
//===----------------------------------------------------------------------===//
enum class EventType {
  None = 0,
  KeyPress,
  KeyRelease,
  MousePress,
  MouseRelease,
  MouseMove,
  WindowClose,
  WindowResize
};

//===-- EventCategory -----------------------------------------------------===//
// A bitmask to help check what category events are in.
//===----------------------------------------------------------------------===//
enum class EventCategory {
  None = 0,
  KeyEvent = 1 << 0,
  MouseEvent = 1 << 1,
  WindowEvent = 1 << 2
};

//===-- Event -------------------------------------------------------------===//
// An abstract event type that all events inherit from.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Event {
public:
  virtual ~Event() = default;

  // Reflection
  virtual const char* getName() const = 0;
  virtual std::string getString() const { return getName(); }
  virtual std::string toString() const = 0;

  virtual EventType getEventType() const = 0;

  // A flag that signals that the event has been handled.
  bool handled{false};

protected:
  friend class EventDispatch;
};

//===-- EventDispatch -----------------------------------------------------===//
// Used to link functions to an event type then dispactch events of that type
// to it.
//===----------------------------------------------------------------------===//
class EventDispatch {
  template <typename T> using eventFunction = std::function<bool(T&)>;

public:
  EventDispatch(Event& e) : event(e) {}

  template <typename T> bool dispatch(eventFunction<T> func) {
    if (event.getEventType() == T::getStaticType()) {
      event.handled = func(*(T*)&event);
      return true;
    }

    return false;
  }

private:
  Event& event;
};

// Logging function.
inline std::ostream& operator<<(std::ostream& os, Event& e) {
  return os << e.toString();
}

} // namespace Trundle
