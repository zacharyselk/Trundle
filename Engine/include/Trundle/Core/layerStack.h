//===-- layerStack.h -------------------------------------------------------===//
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
//===-----------------------------------------------------------------------===//

#pragma once

// A simple stack-like data structure that maintains the ordering of when layers
// should be handled. The stack is split in two segements; normal layers in the
// bottom segement and overlay (UI) layers in the upper segement. When proccessed
// iterators will look from the top to the bottom of the stack for ordering
// (newest to oldest).

#include <Trundle/common.h>
#include <Trundle/Core/core.h>
#include <Trundle/Core/layer.h>


namespace Trundle {

  class TRUNDLE_API LayerStack {
  public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popLayer(Layer* layer);
    void popOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin()  { return layers.begin(); }
    std::vector<Layer*>::iterator end()  { return layers.end(); }

  private:
    std::vector<Layer*> layers;

    // Points to the end of the normal layers on the stack (overlay layers are
    // above)
    // TODO: Rename
    std::vector<Layer*>::iterator it;
  };

}
