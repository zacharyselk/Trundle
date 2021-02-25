//===-- commandLine.h -----------------------------------------------------===//
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
/// Handles the command line arguments for the Engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>

namespace Trundle {

//===----------------------------------------------------------------------===//
/// @brief A structure to pass around all recognized command line arguments.
//===----------------------------------------------------------------------===//
struct CommandLineArgs {
    bool headless{false};
};

/// @brief Parses the raw command line arguments into a @ref CommandLineArgs.
CommandLineArgs parseCommandLine(int* argc, char** argv, char** envp) {
    CommandLineArgs args;
    for (size_t i = 1; i < *argc; ++i) {
        if (strcmp(argv[i], "--headless") == 0) {
            args.headless = true;
            Log::Info("Running in headless mode");
        }
    }

    return args;
}

} // namespace Trundle