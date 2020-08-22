//===-- log.h --------------------------------------------------------------===//
//
// Copyright 2020 Zachary Selk
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
//===-----------------------------------------------------------------------===//
//
// A basic logging system for the engine that defines 6 different types of
// output messages: Trace, Info, Debug, Warning, Error, and Critical. The level
// of which these messages are output is defined at build time with the
// TRUNDLE_LEVEL macro.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/core.h>

#if !defined(TRUNDLE_LEVEL)
#define TRUNDLE_LEVEL 1
#endif


namespace Trundle {
namespace Log {
namespace details {
  enum LogLevel {
    Trace=1,
    Info=2,
    Debug=3,
    Warn=4,
    Error=5,
    Critical=6,
    None=7
  };

}

 namespace Color {
   const std::string red("\033[0;31m");
   const std::string orange("\033[0;33m");
   const std::string yellow("\033[1;33m");
   const std::string green("\033[0;32m");
   const std::string blue("\033[0;34m");
   const std::string cyan("\033[0;36m");
   const std::string purple("\033[0;35m");
   const std::string white("\033[1;37m");
 }


  constexpr int LoggingLevel = TRUNDLE_LEVEL;

  template<typename T>
  void Log(const details::LogLevel &level, const T &msg) {
    std::cout << msg << '\n';
  }

  template<typename T>
  void Trace(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Trace) {
        std::cout << Color::white << "[TRACE]   ";
        Log(details::LogLevel::Trace, msg);
    }
  }

  template<typename T>
  void Info(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Info) {
        std::cout << Color::green << "[INFO]    ";
        Log(details::LogLevel::Info, msg);
    }
  }

  template<typename T>
  void Debug(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Debug) {
        std::cout << Color::orange << "[DEBUG]   ";
        Log(details::LogLevel::Debug, msg);
    }
  }

  template<typename T>
  void Warn(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Warn) {
        std::cout << Color::yellow << "[WARNING] ";
        Log(details::LogLevel::Warn, msg);
    }
  }

  template<typename T>
  void Error(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Error) {
        std::cout << Color::red << "[ERROR]   ";
        Log(details::LogLevel::Error, msg);
    }
  }

  template<typename T>
  void Critical(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Critical) {
        std::cout << Color::cyan << "[CRITICAL] ";
        Log(details::LogLevel::Critical, msg);
    }
  }
}
}
