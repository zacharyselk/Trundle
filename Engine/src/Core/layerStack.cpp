//===-- layerStack.cpp ----------------------------------------------------===//
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
#include <Trundle/Core/layerStack.h>

namespace Trundle {

LayerStack::LayerStack() : layers{}, it{0} {}

LayerStack::~LayerStack() {
  for (Layer* layer : layers) {
    delete layer;
  }
}

void LayerStack::pushLayer(Layer* layer) {
  layers.emplace(layers.begin() + it, layer);
  ++it;
  layer->onAttach();
}

void LayerStack::pushOverlay(Layer* overlay) {
  layers.emplace_back(overlay);
  overlay->onAttach();
}

void LayerStack::popLayer(Layer* layer) {
  auto findIt = std::find(layers.begin(), layers.end(), layer);
  if (findIt != layers.end()) {
    layers.erase(findIt);
    --it;
  }
}

void LayerStack::popOverlay(Layer* overlay) {
  auto findIt = std::find(layers.begin(), layers.end(), overlay);
  if (findIt != layers.end()) {
    layers.erase(findIt);
  }
}

} // namespace Trundle
