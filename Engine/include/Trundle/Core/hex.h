//===-- hex.h -------------------------------------------------------------===//
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
/// A representation for hex values.
//
//===----------------------------------------------------------------------===//
#pragma once

namespace Trundle {

//===-- Hex ---------------------------------------------------------------===//
/// @brief Container for 32 bit hex values.
///
/// Mainly used for color, this class handles hex converstions and breaks the
/// values up into color channels.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Hex {
public:
  /// @brief Default constructor.
  ///
  /// Constructs a hex number with the default value of 0x00000000
  Hex();
  Hex(uint32_t v);
  Hex(std::string color);
  Hex(Color color);

  uint32_t red();
  uint32_t green();
  uint32_t blue();
  uint32_t alpha();
  uint32_t getValue();

  void setRed(uint32_t v);
  void setRed(std::string v);
  void setGreen(uint32_t v);
  void setGreen(std::string v);
  void setBlue(uint32_t v);
  void setBlue(std::string v);
  void setAlpha(uint32_t v);
  void setAlpha(std::string v);
  void setValue(uint32_t v);

  std::string toString();
  void print();

private:
  uin32_t value;
};

} // namespace Trundle