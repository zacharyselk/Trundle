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
/// The MacOS implementation for creating a window.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/window.h>
#include <GLFW/glfw3.h>

namespace Trundle {

//===-- MacOSWindow -------------------------------------------------------===//
/// @brief A representation of a window from MacOS.
///
/// An object that is used to interface with a window from the operating
/// system.
//===----------------------------------------------------------------------===//
class MacOSWindow : public Window {
public:
  /// @brief Default constructor
  ///
  /// @param[in] properties The properties for the new window.
  MacOSWindow(const WindowProperties& properties);

  /// @brief Default virtual destructor.
  virtual ~MacOSWindow();

  /// @brief Updates the window.
  ///
  /// Called every frame in order to update the window to show what has been
  /// rendered.
  void onUpdate() override final;

  /// @brief Returns the width of the window.
  ///
  /// Simple getter for the window width.
  /// @return The width of the window.
  uint32_t getWidth() override final;

  /// @brief Returns the height of the window.
  ///
  /// Simple getter for the window height.
  /// @return The height of the window.
  uint32_t getHeight() override final;

  /// @brief Setter for v-sync.
  ///
  /// An interface used to enable and disable vSync for the window.
  /// @param[in] enable True to enable v-sync, false to disables it.
  void setVSync(bool enable) override final;

  /// @brief Getter for v-sync.
  ///
  /// Gets the current status of v-sync for the window.
  /// @return True if v-sync is enabled, false otherwise.verride final;
  bool isVSync() const;

  /// @brief Getter for the raw window handler.
  ///
  /// Returns a pointer to the raw window object that is native to the
  /// operating system.
  /// @return A void pointer to the window object.
  void* getNativeWindow() const override final;

private:
  // Initailizes the window.
  virtual void init(const WindowProperties& properties);
  // Tears down the window.
  virtual void shutdown();

  /// @brief Data used as a GLFW window user pointer.
  ///
  /// In GLFW a window pointer is a struct with all the relivant information
  /// pertaining to callbacks contained by it.
  struct WindowData {
    std::string title;
    uint32_t width, height;
    bool vSync;

    EventCallback callback;
  };

  // The window's user pointer
  WindowData data;
  // A raw pointer to the windows
  GLFWwindow* window;
  // The event handler callback.
  EventCallback callback;
};

} // namespace Trundle
