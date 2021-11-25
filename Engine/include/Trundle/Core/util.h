//===-- util.h ------------------------------------------------------------===//
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
/// Provides utilities that are core to the interal operation of the Engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <memory>

// On Windows we need to decorate all API classes (classes that will be used
// by the driver) so that dynamic linking is functional. This is only needed
// on windows however, so every other OS evaluates TRUNDLE_API to be an empty
// macro.
#if defined(TRUNDLE_OS_WINDOWS)
#if defined(TRUNDLE_BUILD_LIB)
#define TRUNDLE_API __declspec(dllexport)
#else
#define TRUNDLE_API __declspec(dllimport)
#endif
#else // #if !defined(TRUNDLE_OS_WINDOWS)
#define TRUNDLE_API
#endif
