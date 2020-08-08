#pragma once

#include <Trundle/trundle.hpp>
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
    // on top)
    // TODO: Rename
    std::vector<Layer*>::iterator it;
  };

}
