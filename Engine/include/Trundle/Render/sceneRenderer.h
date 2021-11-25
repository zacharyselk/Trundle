//===-- sceneRenderer.h ---------------------------------------------------===//
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
// In charge of rendering a scene.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Render/renderingQueue.h>
#include <Trundle/Util/primitives.h>
#include <Trundle/common.h>

namespace Trundle {

namespace OpenGL {
class SceneRenderer;
}

class Triangle;

//===-- SceneRenderer -----------------------------------------------------===//
// API that is used to hold the tasks needed to render a scene, then render
// them.
//===----------------------------------------------------------------------===//
class TRUNDLE_API SceneRenderer {
public:
  // TODO: Add flag for what to clear.
  virtual void clear();
  virtual void start();
  // TODO: end will have no idea when frame is over when we start multithreading
  virtual void end();
  virtual void submit(const RenderingTask& task);
  void submit(const VertexArray& a, const Shader& s,
              const std::vector<Uniform>& u);
  void submit(const Triangle& t);

  static SceneRenderer create(const Renderer& r);

private:
  Renderer renderer;
};
//===----------------------------------------------------------------------===//

} // namespace Trundle