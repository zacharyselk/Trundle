//===-- mouseEvent.h ------------------------------------------------------===//
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
/// Represents the components of an event from the mouse.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Events/event.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- MouseButtonEvent --------------------------------------------------===//
/// @brief Contains information unique to a mouse button event.
///
/// An inherited class of @ref Event to describe a mouse button event.
//===----------------------------------------------------------------------===//
class TRUNDLE_API MouseButtonEvent : public Event {
public:
  /// @brief A public getter for the mouse key code.
  ///
  /// @return the key code of the button that was pressed.
  int getMouseCode() const;

protected:
  /// @brief A protected constructor so that only children classes can
  ///        instantiate.
  ///
  /// @param[in] mouseCode The key code of the mouse button that is involved
  ///                      with this event.
  MouseButtonEvent(int mouseCode);

  /// Storage for the key code of the mouse button involved with the event. 
  int mouseCode{-1};
};

//===-- MousePressEvent ---------------------------------------------------===//
/// @brief An event that represents when a mouse button has been clicked.
///
/// A child class of @ref MouseButtonEvent that represents an @ref Event when
/// there is a button pressed from a mouse.
//===----------------------------------------------------------------------===//
class TRUNDLE_API MousePressEvent : public MouseButtonEvent {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] mouseCode The key code of the button pressed on the mouse.
  MousePressEvent(int mouseCode);

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
  /// Returns a string containing the key code of the button on the mouse that
  /// was pressed.
  /// @return A string describing this event.
  virtual std::string toString() const override final;
};

//===-- MouseReleaseEvent -------------------------------------------------===//
/// @brief An event that represents when a mouse button has been released.
///
/// A child class of @ref MouseButtonEvent that represents an @ref Event when
/// there is a button released from a mouse.
//===----------------------------------------------------------------------===//
class TRUNDLE_API MouseReleaseEvent : public MouseButtonEvent {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] mouseCode The key code of the button released on the mouse.
  MouseReleaseEvent(int mouseCode);

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
  /// Returns a string containing the key code of the button on the mouse that
  /// was released.
  /// @return A string describing this event.
  virtual std::string toString() const override final;
};

//===-- MouseMoveEvent ----------------------------------------------------===//
/// @brief An event that represents when a mouse has moved.
///
/// A child class of @ref Event that represents an event when a there is
/// movement from a mouse.
//===----------------------------------------------------------------------===//
class TRUNDLE_API MouseMoveEvent : public Event {
public:
  /// @brief Default constructor
  ///
  /// @param[in] x The x coordinate of where the mouse is now at.
  /// @param[in] y The y coordinate of where the mouse is now at.
  MouseMoveEvent(double x, double y);

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
  /// Returns a string containing the position where the mouse has moved to.
  /// @return A string describing this event.
  virtual std::string toString() const override final;

  /// @brief Gets the x and y coordinates of the mouse.
  ///
  /// @return A tuple containing the x and y coordinates.
  std::tuple<double, double> getPosition() const;

private:
  // Storage for the x and y coordinates of the mouse.
  double x = 0;
  double y = 0;
};

} // namespace Trundle
