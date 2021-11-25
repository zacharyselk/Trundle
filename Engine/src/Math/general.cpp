//===-- general.cpp -------------------------------------------------------===//
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
#include <Trundle/Math/general.h>

uint64_t Trundle::math::fibonacci(uint64_t n) {
  double phi = (1.0 + sqrt(5)) / 2.0;
  return round(pow(phi, n) / sqrt(5));
}

// Slow linear time algorithm. Used for testing purposes only.
uint64_t Trundle::math::fibonacci_linear(uint64_t n) {
  uint64_t total = 0;
  uint64_t minus1 = 0;
  uint64_t minus2 = 1;

  for (uint64_t i = 0; i < n; ++i) {
    total = minus1 + minus2;
    minus2 = minus1;
    minus1 = total;
  }

  return total;
}
