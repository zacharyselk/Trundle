//===-- layerStack.h ------------------------------------------------------===//
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
/// A simple stack-like data structure that maintains the ordering of when
/// layers should be handled. The stack is split in two segements; normal
/// layers in the bottom segement and overlay (UI) layers in the upper
/// segement. When proccessed iterators will look from the top to the bottom 
/// of the stack for ordering (newest to oldest).
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/layer.h>
#include <Trundle/Core/pointer.h>
#include <Trundle/Core/util.h>

namespace Trundle {

class TRUNDLE_API LayerStack {
public:
  /// @brief Default constructor.
  LayerStack();

  /// @brief Default destructor.
  ~LayerStack();

  /// @brief Adds a new layer to the stack.
  ///
  /// @param[in] layer The layer to add to the stack.
  void pushLayer(Ref<Layer> layer);

  /// @brief Adds an overlayer layer to the stack.
  ///
  /// Overlay layers are special layers that sit on the top-most portion of
  /// the stack and are used for layers that control the overlay. This is so
  /// that overlay layers have a chance to handle @ref Events first.
  /// @param[in] overlay The layer to add to the stack.
  void pushOverlay(Ref<Layer> overlay);

  /// @brief Removes a specific layer from the stack.
  ///
  /// @param[in] layer The layer to remove from the stack.
  void popLayer(Ref<Layer> layer);

  /// @brief Removes a specific overlay layer from the stack.
  ///
  /// Overlay layers are special layers that sit on the top-most portion of
  /// the stack and are used for layers that control the overlay. This is so
  /// that overlay layers have a chance to handle @ref Events first.
  /// @param[in] overlay The layer to remove from the stack.
  void popOverlay(Ref<Layer> overlay);

  /// @brief Returns an iterator to the begining of the stack.
  ///
  /// Allows for looping through the stack.
  /// @return An iterator that points to the begining of the stack.
  std::vector<Ref<Layer>>::reverse_iterator begin();

  /// @brief Returns an iterator to the end ofthe stack.
  ///
  /// Allows for looping through the stack.
  /// @returns An iterator that points to the end of the stack.
  std::vector<Ref<Layer>>::reverse_iterator end();

  /// @breif Returns the size of the stack.
  ///
  /// Returns the number of layers that are currently in the stack.
  /// return The number of layers in the stack.
  size_t size();

private:
  // Our representation of the stack of layers is a simple vector.
  std::vector<Ref<Layer>> layers;

  // An index pointer to the current top of the stack of normal layers (and not
  // overlay layers).
  size_t it;
};

} // namespace Trundle