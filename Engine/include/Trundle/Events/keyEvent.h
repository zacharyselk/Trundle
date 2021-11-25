//===-- keyEvent.h --------------------------------------------------------===//
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
/// Represents the components of an event from the keyboad.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Events/event.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- KeyEvent ----------------------------------------------------------===//
/// @brief Contains information unique to a keyboard event.
///
/// An inherited class of @ref Event to describe a keyboard input event.
//===----------------------------------------------------------------------===//
class TRUNDLE_API KeyEvent : public Event {
public:
  /// @brief A public getter for the key code.
  ///
  /// Returns the key code that this object was instantiated with.
  /// @return The key code
  int getKeyCode() const;

protected:
  /// @brief A protected constructor so that only children classes can
  ///        instantiate.
  ///
  /// This class contains the code that is common amongst the two types of
  /// events that a keyboard can produce, a key press event and a key release
  /// event.
  /// @param[in] keyCode The keycode of the key that is involved with this
  ///                    event.
  KeyEvent(int keyCode);

  /// @brief The key code of the key that is involved with this event.
  int keyCode{-1};
};

//===-- KeyPressEvent -----------------------------------------------------===//
/// @brief An event for when a key on the keyboard is pressed down.
///
/// A child class of @ref KeyEvent that represents an @ref Event when a key is
/// pressed on the keyboard.
//===----------------------------------------------------------------------===//
class TRUNDLE_API KeyPressEvent : public KeyEvent {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] keyCode The key code of the key that triggered this event.
  /// @param[in] repeatEvent Indicates whether or not this is a repeated event
  ///                        ie. if the key is being held down.
  KeyPressEvent(int keyCode, bool repeatEvent);

  /// @brief A static function to retrieve the @ref EventType of this event.
  ///
  /// @return The type of event this object represents.
  static EventType getStaticType();

  /// @brief A virtual function to retrieve the @ref EventType of this event.
  ///
  /// This function allows owners of an @ref Event pointer to retrieve the
  /// @ref EventType of it.
  /// @return The type of event this object represents.
  virtual EventType getEventType() const override final;

  /// @brief A virtual function that returns the name of this @ref Event.
  ///
  /// This function allows owners of an @ref Event pointer to retrieve the
  /// name of the event.
  /// @return The event name.
  virtual const char* getName() const override final;

  /// @brief Gets a string that describes this event.
  ///
  /// Returns a string containing the key code and whether or not this is a
  /// repeated event in a nicely formatted string.
  /// @return A string describing this event.
  std::string toString() const override final;

private:
  bool repeatEvent = false;
};

//===-- KeyReleaseEvent ---------------------------------------------------===//
/// @brief An event for when a key on the keyboard is released down.
///
/// A child class of @ref KeyEvent that represents an @ref Event when a key is
/// released on the keyboard.
//===----------------------------------------------------------------------===//
class TRUNDLE_API KeyReleaseEvent : public KeyEvent {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] keyCode The key code of the key that triggered this event.
  KeyReleaseEvent(int keyCode);

  /// @brief A static function to retrieve the @ref EventType of this event.
  ///
  /// @return The type of event this object represents.
  static EventType getStaticType();

  /// @brief A virtual function to retrieve the @ref EventType of this event.
  ///
  /// This function allows owners of an @ref Event pointer to retrieve the
  /// @ref EventType of it.
  /// @return The type of event this object represents.
  virtual EventType getEventType() const override final;

  /// @brief A virtual function that returns the name of this @ref Event.
  ///
  /// This function allows owners of an @ref Event pointer to retrieve the
  /// name of the event.
  /// @return The event name.
  virtual const char* getName() const override final;

  /// @brief Gets a string that describes this event.
  ///
  /// Returns a string containing the key code in a nicely formatted string.
  /// @return A string describing this event.
  std::string toString() const override final;
};

} // namespace Trundle
