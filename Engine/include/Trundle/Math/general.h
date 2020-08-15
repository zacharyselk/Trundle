//===-- general.h ----------------------------------------------------------===//
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

#pragma once

// The start of a math library however this should propbably be removed as we
// are currently using the eigan libary for math.

#include <Trundle/common.h>


namespace Trundle {
namespace math {

uint64_t fibonacci(uint64_t);
uint64_t fibonacci_linear(uint64_t);

}; // namespace math
}; // namespace Trundle
