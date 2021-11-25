//===-- file.cpp ----------------------------------------------------------===//
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
#include <Trundle/Util/file.h>

namespace Trundle {

File::File(const std::string& filename) { path = filename; }

std::string File::read() {
  std::ifstream file;
  file.open(path, std::ifstream::in);

  std::string ret;
  char buffer[4096];
  while (file.read(buffer, sizeof(buffer))) {
    ret.append(buffer, sizeof(buffer));
  }
  ret.append(buffer, file.gcount());
  return ret;
}

} // namespace Trundle