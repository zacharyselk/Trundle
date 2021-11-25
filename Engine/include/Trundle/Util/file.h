//===-- file.h ------------------------------------------------------------===//
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
/// Defines a cross platform file object.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>

namespace Trundle {

//===-- File --------------------------------------------------------------===//
/// @brief Utility class for file handling.
//===----------------------------------------------------------------------===//
class File {
public:
  File() = delete;

  /// @brief Default constructor.
  ///
  /// @param[in] filename The path to the file to use.
  File(const std::string& filename);

  /// @brief Reads file and returns it as a string.
  ///
  /// Takes the file path and reads the entirty of that file into a string.
  /// @return A string containing the contents of the file.
  std::string read();

private:
  std::filesystem::path path;
};

} // namespace Trundle