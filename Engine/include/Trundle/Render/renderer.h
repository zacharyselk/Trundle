//===-- renderer.h --------------------------------------------------------===//
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
// Contains the information needed to instruct where to render and what
// backend should be used to render it.
//
//===----------------------------------------------------------------------===//
#pragma once

namespace Trundle {

enum RenderingAPI { None = 0, OpenGLAPI = 1 };

//===-- Renderer ----------------------------------------------------------===//
// A cookie that is used by the rendering API to make decisions when
// rendering.
// TODO: Rename to RenderingContext.
//===----------------------------------------------------------------------===//
class Renderer {
public:
  Renderer(RenderingAPI api);

  RenderingAPI getAPI() const { return api; }

private:
  RenderingAPI api;
};

} // namespace Trundle
