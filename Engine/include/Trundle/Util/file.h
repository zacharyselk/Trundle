//===-- file.h ------------------------------------------------------------===//
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
// A collection of utility functions to work with files, either virtual or
// physical.
//
//===----------------------------------------------------------------------===//
#include <Trundle/common.h>

namespace Trundle {

// Returns whether or not a string is a file path
bool isFilePath(const std::string& str) {
  // TODO: Make more robust and check the (virtual) file system.
  std::string::size_type pos = str.rfind('.');

  // Check to see if a period exists in the string and if it looks like a
  // file extension.
  if (pos == std::string::npos || str.size() - pos > 3 || str.size() == pos) {
    return false;
  } else {
    return true;
  }
}

// Reads in a file and returns it as a string.
// TODO: Add support for the virtual file systems when one is added.
std::string readFile(const std::string& filepath) {
  std::string file("");
  std::ifstream istream(filepath, std::ios::binary);

  if (!istream.is_open()) {
    Log::Error("Failed to open " + filepath);
    return file; // TODO: Handle this better.
  } else {
    istream.seekg(0, std::ios::end);
    file.reserve(istream.tellg());
    istream.seekg(0, std::ios::beg);
    file.assign(std::istreambuf_iterator<char>(istream),
                std::istreambuf_iterator<char>());
  }

  return file;
}

} // namespace Trundle