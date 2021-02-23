//===-- application.h -----------------------------------------------------===//
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
/// The application class is a singlton that contains the main game loop for the
/// engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/util.h>
#include <Trundle/common.h>

namespace Trundle {

//===----------------------------------------------------------------------===//
/// @brief A base class for the main application running in the Engine.
///
/// @ref Application is used as a base class so that user code may be linked
/// into the Engine with it.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Application {
public:
  /// @brief Default constructor.
  Application();

  /// @brief Default destructor.
  ~Application();

  /// @brief Main game loop of the Engine
  ///
  /// Defines the game loop for the Engine. The game loop is a loop that is
  /// run on each tick or frame of the game and consits of a logic calcualtion
  /// phase and a rendering phase.
  void run();

  /// @brief A getter for the singleton instance of the @ref Application
  ///
  /// As @ref Application defines how the program is run, it is implemented as
  /// a singleton and @ref get returns a pointer to the singleton instance.
  /// @return A pointer to the singleton instance of the @ref Application.
  inline static Application* get() { return instance; }

  // Returns a pointer to the window.
  //inline Window& getWindow() { return *window; }

private:
  static Application* instance;
  bool running{true};
};

// Defined by the driver as an entry point into the engine.
/// @brief External function that describes how to initalize the 
///        @ref Application.
///
/// This function is used as a stub so that the user can dictate how the
/// @ref Application is initalized. In turn this function is called by the
/// Engine on startup to create the @ref Application.
/// @param argc[in] The number of arguments passed.
/// @param argv[in] A list of the arguments passed.
/// @param envp[in] A list of the environment variables.
/// @return A pointer to the created @ref Application.
Application* CreateApplication(int* argc, char** argv, char** envp);

}; // namespace Trundle