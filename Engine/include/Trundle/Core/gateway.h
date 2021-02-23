//===-- gateway.h ---------------------------------------------------------===//
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
/// Provides the entry point for the code that uses an Application defined by
/// the driver to run the Engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/common.h>

/// @brief An external hook that allows the application code to be run by the
///        Engine.
/// 
/// CreateApplication must be defined by the application driver in order for any
/// user code to be hooked into the Engine.
/// @param argc[in] The standard argc that is passed to main.
/// @param argv[in] The standard argv that is passed to main.
/// @param envp[in] The standard envp that is passed to main.
/// @return A pointer to an @ref Application object that will be run by the
///         Engine.
extern Trundle::Application* Trundle::CreateApplication(int* argc, char** argv,
                                                        char** argp);

// Running on Windows will eventually be done through winMain() rather than
// main().
#if defined(_WIN32)

int main(int argc, char** argv, char** envp) {
  Trundle::Log::Debug("Starting Engine\n");
  Trundle::Application* app = Trundle::CreateApplication(&argc, argv, envp);
  //app->run();
  //delete app;
  Trundle::Log::Debug("Application Closed\n");
  std::cout << Trundle::Log::Color::white;
}

#else

int main(int argc, char** argv, char** envp) {
  Trundle::Log::Debug("Starting the Engine");
  Trundle::Application* app = Trundle::CreateApplication(&argc, argv, envp);
  //app->run();
  //delete app;
  Trundle::Log::Debug("Application Closed");
  std::cout << Trundle::Log::Color::white;
}

#endif