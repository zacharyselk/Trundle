//===-- pointer.h ---------------------------------------------------------===//
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
/// Provides smart pointers for the Engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <memory>
#include <utility>

namespace Trundle {

//===-- Ref ---------------------------------------------------------------===//
/// @brief A reference pointer to a peice of data.
///
/// Allows for multiple refrences to a particualr peice of data which is
/// destroyed after all refrences are destroyed.
//===----------------------------------------------------------------------===//
template <typename T>
using Ref = std::shared_ptr<T>;

//===-- Own ---------------------------------------------------------------===//
/// @brief A owning pointer to a peice of data.
///
/// The owning pointer is the only pointer that may point to a piece of data.
/// When the owning pointer is destroyed the data is also destroyed.
//===----------------------------------------------------------------------===//
template <typename T>
using Own = std::unique_ptr<T>;

//===-- View --------------------------------------------------------------===//
/// @brief A pointer that can view the data of a refrence pointer.
///
/// A viewing pointer is only allowed to view a piece of data and cannot
/// modify it. Viewing pointers become invalidated when the data they
/// referencing is destoryed.
//===----------------------------------------------------------------------===//
template <typename T>
using View = std::weak_ptr<const T>;

} // namespace Trundle