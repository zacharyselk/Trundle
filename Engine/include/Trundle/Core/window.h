//===-- window.h ----------------------------------------------------------===//
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
/// An abstract base class for the window provided by the OS. This abstraction
/// needs to have a inherited implementation for each OS supported by Trundle.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Events/event.h>
#include <Trundle/common.h>

namespace Trundle {

//==-- WindowProperties ---------------------------------------------------===//
/// @brief A collection of properties that describe a window.
///
/// A struct used to pass around and configure the properties of a window.
//===----------------------------------------------------------------------===//
struct WindowProperties {
  /// The name that appears at the top of the window.
  std::string title;
  /// The width of the window.
  uint32_t width;
  /// The height of the window.
  uint32_t height;
  /// A flag for determining if vSync should be enabled.
  bool vSync{false};

  /// @brief Default constructor
  ///
  /// Constructs the information for a window.
  /// @param[in] w The width of the window.
  /// @param[in] h The height of the window.
  /// @param[in] str The name of the window.
  WindowProperties(uint32_t w = 1280, uint32_t h = 720,
                   const std::string& str = "Trundle")
      : title(str), width(w), height(h) {}
};

//===-- Window ------------------------------------------------------------===//
/// @brief A representation of a window from the OS.
///
/// An object that is used to interface with a window from the operating
/// system.
//===----------------------------------------------------------------------===//
class Window {
public:
  /// @brief An alias for function callback for events.
  using EventCallback = std::function<void(Event&)>;

  /// @brief Default virtual destructor.
  virtual ~Window() {}

  /// @brief Updates the window.
  ///
  /// Called every frame in order to update the window to show what has been
  /// rendered.
  virtual void onUpdate() = 0;

  /// @brief Returns the width of the window.
  ///
  /// Simple getter for the window width.
  /// @return The width of the window.
  virtual uint32_t getWidth() = 0;

  /// @brief Returns the height of the window.
  ///
  /// Simple getter for the window height.
  /// @return The height of the window.
  virtual uint32_t getHeight() = 0;

  /// @brief Sets a callback to handle @ref Event\ s that occure.
  ///
  /// This function alls callbacks to be used which in turn allows for events
  /// to be handled without the need for polling.
  /// @param[in] callback The callback function for which will be used on
  ///                     events handled by the window.
  virtual void setEventCallback(const EventCallback& callback) = 0;

  /// @brief Setter for v-sync.
  ///
  /// An interface used to enable and disable vSync for the window.
  /// @param[in] enable True to enable v-sync, false to disables it.
  virtual void setVSync(bool enable) = 0;

  /// @brief Getter for v-sync.
  ///
  /// Gets the current status of v-sync for the window.
  /// @return True if v-sync is enabled, false otherwise.
  virtual bool isVSync() const = 0;

  /// @brief Getter for the raw window handler.
  ///
  /// Returns a pointer to the raw window object that is native to the
  /// operating system.
  /// @return A void pointer to the window object.
  virtual void* getNativeWindow() const = 0;

  /// @brief Creates a new window
  ///
  /// A static method used to create a new window.
  /// @param[in] properties The properties for the new window.
  /// @return A pointer to the new window.
  static Window*
  create(const WindowProperties& properties = WindowProperties());
};

} // namespace Trundle