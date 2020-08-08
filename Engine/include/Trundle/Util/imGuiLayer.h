#pragma once

#include <Trundle/trundle.hpp>
#include <Trundle/Core/core.h>
#include <Trundle/Core/layer.h>


struct ImVec4;

namespace Trundle {

  class TRUNDLE_API ImGuiLayer : public Layer {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void onAttach() override final;
    void onDetach() override final;
    void onUpdate() override final;
    void onEvent(Event &event) override final;
    void begin();
    void end();

  private:
    float time;
    ImVec4* backgroundColor;
  };

}
