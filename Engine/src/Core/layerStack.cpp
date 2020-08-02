#include <Trundle/Core/layerStack.h>


namespace Trundle {

LayerStack::LayerStack()
  : layers{}, it(layers.begin())  { }

LayerStack::~LayerStack() {
  for (Layer* layer : layers) {
    delete layer;
  }
}

void LayerStack::pushLayer(Layer* layer) {
  it = layers.emplace(it, layer);
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

}
