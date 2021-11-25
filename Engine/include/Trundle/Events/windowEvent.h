//===-- windowEvent.h -----------------------------------------------------===//
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
/// Represents the components of an event from the window.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Events/event.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- WindowCloseEvent --------------------------------------------------===//
/// @brief An event for when a window is closed.
///
/// An inherited class of @ref Event to describe the event of a window
/// closing.
//===----------------------------------------------------------------------===//
class TRUNDLE_API WindowCloseEvent : public Event {
public:
  /// @brief Defautl constructor.
  WindowCloseEvent();

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
  /// @return A string that describes the event.
  std::string toString() const override final;
};

//===-- WindowResizeEvent -------------------------------------------------===//
/// @brief An event for when a window is resized.
///
/// An inherited class of @ref Event to describe the event of a window
/// resizing.
//===----------------------------------------------------------------------===//
class TRUNDLE_API WindowResizeEvent : public Event {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] w The new width of the window.
  /// @param[in] h The new height of the window.
  WindowResizeEvent(int w, int h);

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
  /// Returns a string containing the new width and height of the window.
  /// @return A string describing this event.
  std::string toString() const override final;

private:
  // Storage for the width and height.
  int width{-1};
  int height{-1};
};

} // namespace Trundle
