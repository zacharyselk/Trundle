//===-- sceneRenderer.cpp -------------------------------------------------===//
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
#include <Trundle/Core/time.h>
#include <Trundle/Platform/OpenGL/sceneRenderer.h>
#include <Trundle/Render/sceneRenderer.h>

namespace Trundle {

//===-- SceneRenderer -----------------------------------------------------===//
SceneRenderer::SceneRenderer(const Renderer& r) : vptr(nullptr) {
  switch (r.getAPI()) {
  // TODO: Implement.
  case RenderingAPI::None:
    break;

  case RenderingAPI::OpenGLAPI:
    vptr = std::make_shared<Trundle::OpenGL::SceneRenderer>();
    break;

  default:
    Log::Error("Unknown graphics API");
    exit(1);
  }
}

void SceneRenderer::clear() { vptr->clear(); }

void SceneRenderer::start() {
  Time::startFrame();
  vptr->start();
}

void SceneRenderer::end() { vptr->end(); }

void SceneRenderer::submit(const RenderingTask& task) { vptr->submit(task); }

void SceneRenderer::submit(const VertexArray& a, const Shader& s,
                           const std::vector<Uniform>& u) {
  submit(std::forward<RenderingTask>(RenderingTask(a, s, u)));
}
//===----------------------------------------------------------------------===//

} // namespace Trundle