//===-- grid.h ------------------------------------------------------------===//
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
/// Defines a grid structure that manages a two dimentional array of
/// rectangles.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Renderer/geometry.h>
#include <lib/c++/math/rational.h>

namespace Trundle {

//===-- Grid --------------------------------------------------------------===//
/// @brief Calculates and represents a 2D grid of rectangular cells.
///
/// This utility class is used to help render objects on a evenly poportioned
/// grid of cells.
//===----------------------------------------------------------------------===//
template <typename T> class Grid {
public:
  /// Defualt constructor.
  ///
  /// @param[in] w The width of the grid.
  /// @param[in] h The height of the grid.
  Grid(T w, T h, T xMarg = 0, T yMarg = 0)
      : gridWidth(w), gridHeight(h), xMargin(xMarg), yMargin(yMarg) {}

  /// @brief Setter for the rectangular cell dimensions.
  ///
  /// Setting the cell dimensions will automatically set (or overwrite) the
  /// number of grid cells as well as the grid margines.
  /// @param[in] width The width of the rectangular cell.
  /// @param[in] height The height of the rectangular cell.
  void setCellDims(T width, T height);

  /// @brief Setter for the grid dimensions using cells as the units.
  ///
  /// Setting the grid dimensions will automatically set (or overwrite) the
  /// cell dimenstions in order to fill the grid to either the borders or to the
  /// margin if there is a margin.
  void setGridDims(T width, T height);

  template <typename U>
  void setMapping(std::function<std::pair<U, U>(T, T)> mapFunc);

  Rect<T> getCell(uint64_t i, uint64_t j) const;

private:
  T gridWidth, gridHeight, xMargin, yMargin;
  T cellWidth, cellHeight, xCellCount, yCellCount;
};

} // namespace Trundle