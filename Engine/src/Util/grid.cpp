//===-- grid.cpp ----------------------------------------------------------===//
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
#include <Trundle/Util/grid.h>
#include <Trundle/Core/log.h>
#include <lib/c++/string/format.h>

namespace Trundle {

template <typename T> void Grid<T>::setCellDims(T width, T height) {
  if (width > (gridWidth - 2 * xMargin)) {
    auto msg =
        z::formatString("Error: attempted to set a cell width of {} on a grid "
                        "of width {} and margin {}. Aborting operation!",
                        width, gridWidth, xMargin);
    Log::Error(msg);
    return;
  }
  if (height > (gridHeight - 2 * yMargin)) {
    auto msg =
        z::formatString("Error: attempted to set a cell height of {} on a grid "
                        "of height {} and margin {}. Aborting operation!",
                        height, gridHeight, yMargin);
    Log::Error(msg);
    return;
  }

  cellWidth = width;
  cellHeight = height;

  // TODO: Add floor to this calculation
  xCellCount = (gridWidth - 2 * xMargin) / cellWidth;
  yCellCount = (gridHeight - 2 * yMargin) / cellHeight;
}

} // namespace Trundle
