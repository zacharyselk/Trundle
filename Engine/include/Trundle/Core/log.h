//===-- log.h -------------------------------------------------------------===//
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
// A basic logging system for the engine that defines 6 different types of
// output messages: Trace, Info, Debug, Warning, Error, and Critical. The level
// of which these messages are output is defined at build time with the
// TRUNDLE_LEVEL macro.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/util.h>

#if !defined(TRUNDLE_LEVEL)
#define TRUNDLE_LEVEL 3
#endif

namespace Trundle {
namespace Log {
namespace details {

/// @brief The levels that a logged message can be so that the log may be
///        filtered as nessisary.
enum LogLevel {
  Trace = 1,
  Info = 2,
  Debug = 3,
  Warn = 4,
  Error = 5,
  Critical = 6,
  None = 7
};

} // namespace details

/// @brief Escape codes for some simple colors to change the color of text in
///        the terminal.
namespace Color {
const std::string red("\033[0;31m");
const std::string orange("\033[0;33m");
const std::string yellow("\033[1;33m");
const std::string green("\033[0;32m");
const std::string blue("\033[0;34m");
const std::string cyan("\033[0;36m");
const std::string purple("\033[0;35m");
const std::string white("\033[1;37m");
const std::string reset("\033[0m");
} // namespace Color

// Default the logging level to an environment variable passed in by the
// compiler.
// TODO: This should be made into a runtime option.
constexpr int LoggingLevel = TRUNDLE_LEVEL;

/// @brief Logs a message to the terminal.
///
/// This function will alway output a log message to the terminal, regardless
/// of the current @ref LoggingLevel.
/// @param[in] msg The message to be output.
template <typename T> void Log(const details::LogLevel&, const T& msg) {
  std::cout << msg << Color::reset << '\n';
}

/// @brief Logs a trace message to the terminal.
///
/// A trace message provides the most verbosity of information and is only
/// output when the @ref LoggingLevel is set to "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Trace(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Trace) {
    std::cout << Color::white << "[TRACE]   ";
    Log(details::LogLevel::Trace, msg);
  }
}

/// @brief Logs an info message to the terminal.
///
/// An info message provides information that about the current state of the
/// Engine and settings that the Engine sets verbosity of information and is
/// only output when the @ref LoggingLevel is set to "Info" or "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Info(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Info) {
    std::cout << Color::green << "[INFO]    ";
    Log(details::LogLevel::Info, msg);
  }
}

/// @brief Logs a debug message to the terminal.
///
/// A debug message provides information that may aid in debugging and is only
/// output when the @ref LoggingLevel is set to "Debug", "Info", or "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Debug(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Debug) {
    std::cout << Color::orange << "[DEBUG]   ";
    Log(details::LogLevel::Debug, msg);
  }
}

/// @brief Logs a warning message to the terminal.
///
/// A warning message provides information that a non-terminating issue has
/// occured and is only output when the @ref LoggingLevel is set to "Warn", 
/// "Debug", "Info", or "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Warn(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Warn) {
    std::cout << Color::yellow << "[WARNING] ";
    Log(details::LogLevel::Warn, msg);
  }
}

/// @brief Logs an error message to the terminal.
///
/// An error message provides information that a recoverable or partially
/// recoverable issue has occured and is only output when the @ref LoggingLevel 
/// is set to "Error", "Warn", "Info", or "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Error(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Error) {
    std::cout << Color::red << "[ERROR]   ";
    Log(details::LogLevel::Error, msg);
  }
}

/// @brief Logs a critical message to the terminal.
///
/// A critical message provides information that a non recoverable issue has 
/// occured and is only output when the @ref LoggingLevel is set to "Critical",
/// "Error", "Warn", "Info", or "Trace".
/// @param[in] msg The message to be output.
template <typename T> void Critical(const T& msg) {
  if constexpr (LoggingLevel <= details::LogLevel::Critical) {
    std::cout << Color::cyan << "[CRITICAL] ";
    Log(details::LogLevel::Critical, msg);
  }
}
} // namespace Log
} // namespace Trundle