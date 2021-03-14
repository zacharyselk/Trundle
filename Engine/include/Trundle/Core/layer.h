//===-- layer.h -----------------------------------------------------------===//
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
/// A base class that allows users to create code that can be added and
/// removed from execution at runtime.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/util.h>
#include <Trundle/Events/event.h>

namespace Trundle {

//===-- Layer -------------------------------------------------------------===//
/// @brief An abstract object that is run by the engine.
///
/// When attached to a scene this object will be run by the engine in the
/// order of which it was added. This allows for custom layers created by the
/// user to be hooked into the engine.
//===----------------------------------------------------------------------===//
class TRUNDLE_API Layer {
public:
  /// @brief Default constructor.
  ///
  /// @param[in] name The name of the layer, used for reflective perposes.
  Layer(const std::string& name = std::string("Layer"));

  /// @brief Default constructor.
  virtual ~Layer();

  /// @brief Function called when the layer is added to the scene.
  virtual void onAttach();
  
  /// @brief Function called when the layer is removed from the scene.
  virtual void onDetach();

  /// @brief Function called on each frame so long as the layer is attached.
  virtual void onUpdate();

  /// @brief Function called when an @ref Event occures.
  ///
  /// This function gives each layer an opportunity to handle an @ref Event if
  /// they choose. Otherwise the event is given to the next layer until it has
  /// been handled.
  /// @param[in,out] event The event to be handled.
  virtual void onEvent(Event& event);
  
  /// @brief A getter function for the layer name.
  ///
  /// @return The name of the layer.
  const std::string& getName();

protected:
  /// The name of the layer.
  std::string name;
};

} // namespace Trundle