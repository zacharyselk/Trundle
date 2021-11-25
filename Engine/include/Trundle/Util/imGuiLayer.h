//===-- imGuiLayer.h ------------------------------------------------------===//
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
// Implments an (overlay) layer that definesthe ImGui UI creation, deletion,
// and interactions.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/core.h>
#include <Trundle/Core/layer.h>
#include <Trundle/Render/sceneRenderer.h>
#include <Trundle/common.h>

struct ImVec4;

namespace Trundle {

class TRUNDLE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void onAttach() override final;
  void onDetach() override final;
  void onUpdate(SceneRenderer&) override final;
  void onEvent(Event& event) override final;
  void begin();
  void end();

private:
  float time;
  bool initalized{false}; // TODO: Remove the need for this.
  ImVec4* backgroundColor;
};

} // namespace Trundle
