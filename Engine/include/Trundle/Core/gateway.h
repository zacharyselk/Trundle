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
#include <Trundle/Core/util.h>
#include <Trundle/common.h>

#include <sstream>

#if defined(TESTING_BUILD)
#include <gtest/gtest.h>

// TODO: Remove this.
#if defined(RUN_HEADLESS)
bool HEADLESS = true;
#else
bool HEADLESS = false;
#endif
#endif

/// @brief An external hook that allows the application code to be run by the
///        Engine.
/// 
/// CreateApplication must be defined by the application driver in order for any
/// user code to be hooked into the Engine.
/// @param[in] argc The standard argc that is passed to main.
/// @param[in] argv The standard argv that is passed to main.
/// @param[in] envp The standard envp that is passed to main.
/// @return A pointer to an @ref Application object that will be run by the
///         Engine.
extern Trundle::Application* Trundle::CreateApplication(int* argc, char** argv,
                                                        char** argp);

#if defined(TESTING_BUILD)
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}

// Running on Windows will eventually be done through winMain() rather than
// main().
#elif defined(_WIN32)

int main(int argc, char** argv, char** envp) {
  Trundle::Log::Debug("Starting Engine\n");
  Trundle::Application* app = Trundle::CreateApplication(&argc, argv, envp);
  app->run();
  delete app;
  Trundle::Log::Debug("Application Closed\n");

  return 0;
}

#else

int main(int argc, char** argv, char** envp) {
  Trundle::Log::Debug("Starting the Engine");
  Trundle::Application* app = Trundle::CreateApplication(&argc, argv, envp);
  app->run();
  delete app;
  Trundle::Log::Debug("Application Closed");

  return 0;
}
#endif