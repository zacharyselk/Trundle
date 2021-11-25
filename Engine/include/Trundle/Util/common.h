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
// Adds helper tools for general use.
// TODO: Move into a different folder.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>

// Debug info
#define LOC " (" << __FILE__ << ": " << __LINE__ << ")\n"
#define CHECK(condition)                                                       \
  {                                                                            \
    if (!(condition)) {                                                        \
      std::cerr << "ASSERT FAILED: " << #condition << LOC;                     \
      exit(1)                                                                  \
    }                                                                          \
  }
#define DIE(msg)                                                               \
  {                                                                            \
    std::cerr << "Error: " << #msg << LOC;                                     \
    exit(1);                                                                   \
  }

namespace common {

// Helper templates for combining a list of lambdas into an anonymous
// struct for use with std::visit() on a std::variant<> sum type.
// E.g.: std::visit(visitors{
//         [&](const firstType &x) { ... },
//         [&](const secondType &x) { ... },
//         ...
//         [&](const auto &catchAll) { ... }}, variantObject);
template <typename... LAMBDAS> struct visitors : LAMBDAS... {
  using LAMBDAS::operator()...;
};

template <typename... LAMBDAS> visitors(LAMBDAS... x)->visitors<LAMBDAS...>;

// Copy a value from one variant type to another.  The types allowed in the
// source variant must all be allowed in the destination variant type.
template <typename TOV, typename FROMV> TOV CopyVariant(const FROMV& u) {
  return std::visit([](const auto& x) -> TOV { return {x}; }, u);
}

}; // namespace common
