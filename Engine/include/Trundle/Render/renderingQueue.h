//===-- renderingQueue.h --------------------------------------------------===//
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
// A task queue for the rendering system.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Render/buffer.h>
#include <Trundle/Render/renderer.h>
#include <Trundle/common.h>

namespace Trundle {

//===-- RenderingTask -----------------------------------------------------===//
// A genaric task that defines a unit of rendering.
//===----------------------------------------------------------------------===//
class RenderingTask {
public:
  RenderingTask(const VertexArray& a) : array(a) {}

  VertexArray array;
};

//===-- RenderingQueue ----------------------------------------------------===//
// A queue that holds a series of tasks waiting to be rendered.
//===----------------------------------------------------------------------===//
class RenderingQueue {
public:
  RenderingQueue() = default;

  void submit(const RenderingTask& task) { queue.push(task); }

  bool empty() { return queue.empty(); }
  void push(const RenderingTask& task) { queue.push(task); }
  void pop() { queue.pop(); }
  RenderingTask& front() { return queue.front(); }

private:
  // TODO: Replace with a threaded queue.
  std::queue<RenderingTask> queue;
};

} // namespace Trundle