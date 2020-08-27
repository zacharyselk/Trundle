//===-- renderingQueue.h ---------------------------------------------------===//
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
// A task queue for the rendering system
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/Render/buffer.h>


namespace Trundle {

namespace OpenGL {
    class SceneRenderer;
}
    
  class RenderingTask {
    public:
    RenderingTask(const VertexArray &a)
      : array(a)  { }

    VertexArray array;
  };

  class RenderingQueue {
  public:
    RenderingQueue() = default;

    void submit(const RenderingTask &task) { queue.push(task); }

    bool empty()  { return queue.empty(); }
    void push(const RenderingTask &task)  { queue.push(task); }
    void pop() { queue.pop(); }
    RenderingTask &front()  { return queue.front(); }

  private:
    // TODO: Replace with a threaded queue
    std::queue<RenderingTask> queue;
  };

    class SceneRenderer {
    public:
        SceneRenderer() = default;
        SceneRenderer(const Renderer &r);
        SceneRenderer(SceneRenderer&&) = default;
        SceneRenderer& operator=(const SceneRenderer &renderer) noexcept
          { vptr = renderer.vptr; return *this; }

        // TODO: Add flag for what to clear
        void clear() { vptr->clear(); }
        void start() { vptr->start(); }
        void end() { vptr->end(); }
        void submit(const RenderingTask &task) { vptr->submit(task); }

        friend class OpenGL::SceneRenderer;
        
    private:
        // Virtual base class for polymorphism.
        class SceneRendererConcept {
        public:
        virtual ~SceneRendererConcept() = default;

        virtual void clear() = 0;
        virtual void start() = 0;
        virtual void end() = 0;
        virtual void submit(const RenderingTask &task) = 0;

        protected:
            RenderingQueue queue;
        };

    // Custom virtual pointer to allow for value semantic polymorphism.
    std::shared_ptr<SceneRendererConcept> vptr;
    };

}