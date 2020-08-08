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

  constexpr int LoggingLevel = TRUNDLE_LEVEL;

  template<typename T>
  void Log(const details::LogLevel &level, const T &msg) {
    std::cout << msg << '\n';
  }

  template<typename T>
  void Trace(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Trace) {
        Log(details::LogLevel::Trace, msg);
    }
  }

  template<typename T>
  void Info(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Info) {
        Log(details::LogLevel::Info, msg);
    }
  }

  template<typename T>
  void Debug(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Debug) {
        Log(details::LogLevel::Debug, msg);
    }
  }

  template<typename T>
  void Warn(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Warn) {
        Log(details::LogLevel::Warn, msg);
    }
  }

  template<typename T>
  void Error(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Error) {
        Log(details::LogLevel::Error, msg);
    }
  }

  template<typename T>
  void Critical(const T &msg) {
    if constexpr (LoggingLevel <= details::LogLevel::Critical) {
        Log(details::LogLevel::Critical, msg);
    }
  }
}
}
