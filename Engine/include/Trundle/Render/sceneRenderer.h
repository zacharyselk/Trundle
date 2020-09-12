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
#include <Trundle/common.h>

namespace Trundle {

namespace OpenGL {
class SceneRenderer;
}

//===-- SceneRenderer -----------------------------------------------------===//
// API that is used to hold the tasks needed to render a scene, then render
// them.
//===----------------------------------------------------------------------===//
class SceneRenderer {
public:
  SceneRenderer() = default;
  SceneRenderer(const Renderer& r);
  SceneRenderer(SceneRenderer&&) = default;
  SceneRenderer& operator=(const SceneRenderer& renderer) noexcept {
    vptr = renderer.vptr;
    return *this;
  }

  // TODO: Add flag for what to clear.
  void clear();
  void start();
  // TODO: end will have no idea when frame is over when we start multithreading
  void end();
  void submit(const RenderingTask& task);
  void submit(const VertexArray& a, const Shader& s,
              const std::vector<Uniform>& u);

  friend class OpenGL::SceneRenderer;

private:
  // Virtual base class for polymorphism.
  class SceneRendererConcept {
  public:
    virtual ~SceneRendererConcept() = default;

    virtual void clear() const = 0;
    virtual void start() const = 0;
    virtual void end() const = 0;
    virtual void submit(const RenderingTask& task) const = 0;

  protected:
    mutable RenderingQueue queue;
  };

  // Custom virtual pointer to allow for value semantic polymorphism.
  std::shared_ptr<SceneRendererConcept> vptr;
};
//===----------------------------------------------------------------------===//

} // namespace Trundle