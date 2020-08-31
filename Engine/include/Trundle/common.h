//===-- common.h ----------------------------------------------------------===//
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
// A header file that includes common library headers, can be compiled as a
// precompiled binary to speedup build times.
//
//===----------------------------------------------------------------------===//

// Algorithms.
#include <algorithm>

// Data structures.
#include <array>
#include <deque>
#include <queue>
#include <string>
#include <vector>

// Data Types.
#include <cstdint>

// Error Handling.
#include <cassert>

// Mathmatics.
#include <cmath>

// Threading.
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

// Utilities.
#include <functional>
#include <memory>
#include <tuple>
//#include <variant>

// TODO: Remove.
#include <iostream>
#include <sstream>
