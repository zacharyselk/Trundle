//===-- color.h -----------------------------------------------------------===//
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
/// A set of standard colors recognized by the engine.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <tuple>

namespace Trundle {

//===-- Color -------------------------------------------------------------===//
/// @brief A structure that contains the 8-bit rgba values used to compose
///        a color.
//===----------------------------------------------------------------------===//
struct Color {
  /// @brief Defualt constructor
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
      : r(r), g(g), b(b), a(a) {}
  Color(uint32_t rgba) {
    a = rgba & 255;
    b = (rgba >> 8) & 255;
    g = (rgba >> 16) & 255;
    r = (rgba >> 24) & 255;
  }

  /// @brief Getter function for the normalized rgba values.
  ///
  /// Returns each color values from the 4 rgba color channels with a values
  /// that range from 0.0 to 1.0 where 0 corrisponds to 0 and 1 corrisponds to
  /// 255.
  ///
  /// @return A tuple containing the 4 normalized color channels.
  std::tuple<float, float, float, float> normalize() const {
    return {static_cast<float>(r) / 255.0, static_cast<float>(g) / 255.0,
            static_cast<float>(b) / 255.0, static_cast<float>(a) / 255.0};
  }

  /// @brief Getter function for the rgba values.
  ///
  /// @return A tuple containing the 4 8-bit color channels.
  std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> rgba() const {
    return {r, g, b, a};
  }

  uint8_t r, g, b, a;
};

namespace Constant {

// A colection of common colors and their associated rgba values.
const Color Aqua(0, 255, 255);
const Color Black(0, 0, 0);
const Color Blue(0, 0, 255);
const Color Fuchsia(255, 0, 255);
const Color Gray(128, 128, 128);
const Color Green(0, 255, 0);
const Color Lime(191, 255, 0);
const Color Maroon(128, 0, 0);
const Color Navy(0, 0, 128);
const Color Olive(128, 128, 0);
const Color Orange(255, 165, 0);
const Color Purple(128, 0, 128);
const Color Red(255, 0, 0);
const Color Silver(192, 192, 192);
const Color Teal(0, 128, 128);
const Color White(255, 255, 255);
const Color Yellow(255, 255, 0);

} // namespace Constant

} // namespace Trundle