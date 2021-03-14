//===-- event.h -----------------------------------------------------------===//
//
// Copyright 2021 Zachary Selk
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
/// The base class for events. An event represents an interaction that the
/// user has with the program, that includes keyboard events, mouse events,
/// and actions performed to the window (ie resizing, closing, etc.).
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/util.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- EventType ---------------------------------------------------------===//
/// @brief A list of the types of events in the Engine.
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
/// @brief A bitmask to help check what category events are in.
//===----------------------------------------------------------------------===//
enum class EventCategory {
  None = 0,
  KeyEvent = 1 << 0,
  MouseEvent = 1 << 1,
  WindowEvent = 1 << 2
};

//===-- Event -------------------------------------------------------------===//
/// @brief The abstract event type that all events inherit from.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Event {
public:
  /// @brief The defualt constructor.
  virtual ~Event() = default;

  /// @brief A reflective function to return the name of the type of event.
  ///
  /// Used mostly for debugging perposes, this function allows events to be
  /// inspected.
  /// @return A const char* of the name.
  virtual const char* getName() const = 0;

  /// @brief  A reflective function to return the name of the type of event.
  ///
  /// Used mostly for debugging perposes, this function allows events to be
  /// inspected.
  /// @return A string of the name.
  // TODO: Remove
  virtual std::string getString() const { return getName(); }

  /// @brief A reflective function to return the event information as a string.
  ///
  /// Used mostly for debugging perposes, this function allows events to be
  /// inspected.
  /// @return A string of the event content.
  virtual std::string toString() const = 0;

  /// @brief Gets the type that this current event is.
  ///
  /// Used mainly by the dispatcher to run events with their appropiot
  /// functions.
  /// @return The type of event that this current object is.
  virtual EventType getEventType() const = 0;

  /// @brief A flag that signals that the event has been handled.
  bool handled{false};

protected:
  friend class EventDispatch;
};

//===-- EventDispatch -----------------------------------------------------===//
/// @brief Links functions to an event type for dispactching evnets.
///
/// Used to create callbacks for the different event types in a nice
/// dispatcher style.
//===----------------------------------------------------------------------===//
class EventDispatch {
  template <typename T> using eventFunction = std::function<bool(T&)>;

public:
  /// @brief Default constructor.
  ///
  /// @param[in,out] e The event to dispatch on.
  EventDispatch(Event& e);

  /// @brief Attempts to dispatch the event with the givent labmda.
  ///
  /// When given a labmda and event type this function will check if event has
  /// the same type as the given event type and if it does it will pass the
  /// event to the given labmda function.
  /// @param[in] func The callback function to handle events.
  /// @return true if this function handled the event, false otherwise.
  template <typename T> 
  bool dispatch(eventFunction<T> func)  {
  if (event.getEventType() == T::getStaticType()) {
    event.handled = func(*(T*)&event);
    return true;
  } else {
    return false;
  }
}

private:
  Event& event;
};

/// @brief Overloading the stream operation with osterams to allow events to be
///        be printable.
inline std::ostream& operator<<(std::ostream& os, Event& e) {
  return os << e.toString();
}

} // namespace Trundle