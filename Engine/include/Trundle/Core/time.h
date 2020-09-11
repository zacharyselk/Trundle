//===-- time.h ------------------------------------------------------------===//
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
//===----------------------------------------------------------------------===//
//
// Handles timing for the engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>

namespace Trundle {

//===-- Time --------------------------------------------------------------===//
// Static timing class that manages the timing elements of the engine such as
// the frame delta time.
//===----------------------------------------------------------------------===//
class Time {
public:
  static void startFrame();
  static double deltaTime();

private:
  Time() = default;

  static std::chrono::high_resolution_clock::time_point frameStartTimestamp;
  static std::chrono::microseconds lastFrameDuration;
};

std::chrono::high_resolution_clock::time_point Time::frameStartTimestamp =
    std::chrono::high_resolution_clock::now();
std::chrono::microseconds Time::lastFrameDuration =
    std::chrono::microseconds(0);

void Time::startFrame() {
  auto now = std::chrono::high_resolution_clock::now();
  lastFrameDuration = std::chrono::duration_cast<std::chrono::microseconds>(
      now - frameStartTimestamp);
  frameStartTimestamp = std::chrono::high_resolution_clock::now();
}

double Time::deltaTime() {
  std::chrono::duration<double> sec =
      std::chrono::duration_cast<std::chrono::duration<double>>(
          lastFrameDuration);
  return sec.count();
}

} // namespace Trundle