//===-- sceneRenderer.h- ---------------------------------------------------===//
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
//
// Defines the SceneRenderer abstraction for OpenGL graphics.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/Render/sceneRenderer.h>


namespace Trundle::OpenGL {

    //===-- SceneRenderer --------------------------------------------------===//
    // Is used to hold the tasks needed to render a scene, then render them.
    //===-------------------------------------------------------------------===//
    class SceneRenderer : public Trundle::SceneRenderer::SceneRendererConcept {
    public:
        SceneRenderer() = default;
        virtual ~SceneRenderer()  { }

        virtual void clear() const override final;
        virtual void start() const override final;
        virtual void end() const override final;
        virtual void submit(const RenderingTask &task) const override final;
    };

}