//===-- input.h -----------------------------------------------------------===//
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
/// Input handling API.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/keyCode.h>
#include <Trundle/Core/util.h>
#include <Trundle/common.h>

// Temp
#include <Trundle/Core/application.h>

namespace Trundle {

//===-- Input -------------------------------------------------------------===//
/// @brief A static singleton that manages which keys are currently pressed.
///
/// This manager acts as a central source for keyboard input into the engine,
/// as a key press is a global event this seems appropriate. This also solves
/// the issue with querying if a key is pressed, due to queries being able to
/// be checked anywhere in code.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Input {
public:
  /// @brief Queries the system to see if a specific key is pressed.
  ///
  /// Checks with the operating system to see if a key is currently pressed,
  /// this is a slower function but is gaurenteed to be correct.
  /// @param[in] keycode The key to query.
  /// @return true if the key is currently pressed and false otherwise.
  static bool isKeyPressed(KeyCode keycode);

  /// @brief Sets the key to be in the *pressed* state
  ///
  /// When a @ref KeyPressEvent has recieved this function is called to hanled
  /// it.
  /// @param[in] keycode The key to set to the *pressed* state.
  static void setKeyDown(KeyCode keycode);

  /// @brief Clears the key from being in the *pressed* state
  ///
  /// When a @ref KeyReleaseEvent has recieved this function is called to hanled
  /// it.
  /// @param[in] keycode The key to set to not being *pressed*.
  static void setKeyUp(KeyCode keycode);

  /// @brief Dispatcher function to handle each key that is pressed.
  ///
  /// Allows arbitrary code to determine how a keypress should be handled.
  /// @param[in] func A function that is run on each of the keys that are
  ///                 currently pressed.
  static void handleKeysDown(std::function<void(KeyCode)> func);

  /// @brief Queries to see if a specific key is pressed.
  ///
  /// Checks to see if the key is currenly in the *pressed* state at the moment
  /// which remains true until the @ref KeyReleaseEvent has been handled.
  /// @param[in] keycode The key to query.
  /// @return true if the key is currently pressed and false otherwise.
  static bool isKeyDown(KeyCode keycode);

  /// @brief Queries to see if a specific key is pressed.
  ///
  /// Checks to see if the key is currenly in the *pressed* state at the moment
  /// which remains true until the @ref KeyReleaseEvent has been handled.
  /// @param[in] keycode The key to query.
  /// @return false if the key is currently pressed and true otherwise.
  static bool isKeyUp(KeyCode keycode);

private:
  Input() = default;

  // Note: Trundle::Key has 325 key codes.
  // A simple bitmask of which keys are currently pressed.
  static std::array<bool, 325> keysDown;
};

} // namespace Trundle