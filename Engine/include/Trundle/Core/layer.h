//===-- layer.h -----------------------------------------------------------===//
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
// An abstraction for the genaric layer type. Used to define interactable
// objects that can be layered one infron of the other. An example of this would
// be UI elements.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/core.h>
#include <Trundle/Events/event.h>
#include <Trundle/common.h>

namespace Trundle {

class TRUNDLE_API Layer {
public:
  Layer(const std::string& name = std::string("Layer")) : name(name) {}
  virtual ~Layer() {}

  // A set of actions that can be performed on a layer
  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate() {}
  virtual void onEvent(Event& event) {}

  // Reflective functions
  inline const std::string& getName() { return name; }

protected:
  // TODO: Gen with reflection code
  std::string name;
};

} // namespace Trundle
