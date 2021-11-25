//===-- util.h ------------------------------------------------------------===//
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
/// Rendering API helper functions.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/log.h>
#include <Trundle/common.h>

namespace Trundle::Rendering {

enum class DataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat2,
  Mat3,
  Mat4
};

/// @brief Static lookup function for the size of a given data type.
///
/// @return The size in bytes of the @ref DataType given.
constexpr uint32_t getSize(DataType type) {
  switch (type) {
  case DataType::Float:
    return 4;
  case DataType::Float2:
    return 4 * 2;
  case DataType::Float3:
    return 4 * 3;
  case DataType::Float4:
    return 4 * 4;
  case DataType::Mat2:
    return 4 * 2 * 2;
  case DataType::Mat3:
    return 4 * 3 * 3;
  case DataType::Mat4:
    return 4 * 4 * 4;
  default:
    Log::Critical("Unknown Rendering::DataType passed");
  }
  return 0;
}

/// @brief Static lookup function for the component size of a given data type.
///
/// Returns the size of an individual comonent in the data type given, eg the
/// component size of DataType::Float3 is the size of a single float and not
/// the aggregate size of an array of three floats.
/// @return The number of bytes the comonent of the data type takes up.
constexpr uint32_t getComponentSize(DataType type) {
  switch (type) {
  case DataType::Float:
  case DataType::Float2:
  case DataType::Float3:
  case DataType::Float4:
  case DataType::Mat2:
  case DataType::Mat3:
  case DataType::Mat4:
    return getSize(DataType::Float);
  default:
    Log::Critical("Unknown Rendering::DataType passed");
  }

  return 0;
}

/// @brief Static lookup function for the number of components in a data type.
///
/// Return the number of individual components in a given data type, eg. the
/// number of components in a DataType::Float2 is two.
/// @return The number of components in the data type.
constexpr uint32_t numberOfComponents(DataType type) {
  switch (type) {
  case DataType::Float:
    return 1;
  case DataType::Float2:
    return 2;
  case DataType::Float3:
    return 3;
  case DataType::Float4:
    return 4;
  case DataType::Mat2:
    return 4;
  case DataType::Mat3:
    return 9;
  case DataType::Mat4:
    return 16;
  default:
    Log::Critical("Unknown Rendering::DataType passed");
  }

  return 0;
}

} // namespace Trundle::Rendering