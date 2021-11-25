//===-- memory.h ----------------------------------------------------------===//
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
// Memory managment tools and systems used by Trundle
//
//===----------------------------------------------------------------------===//
#pragma once

#include <memory>

namespace Trundle {

//===-- @class Ref --------------------------------------------------------===//
/// @brief A wrapper for the std shared pointer
///
/// @ref Ref is a refrence to an object in memory, this object may have many
/// @ref Ref s pointing to it. @ref Ref wraps std::shared_ptr so that it may
/// be modified in the future with relitivly low maintanence costs.
//===----------------------------------------------------------------------===// 
template<typename T>
class Ref : public std::shared_ptr<T> {

};

//===-- 
template<typename T>
using View = std::weak_ptr<T const>;

} // namespace Trundle