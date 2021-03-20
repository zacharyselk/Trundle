//===-- layer.cpp ---------------------------------------------------------===//
//
// Copyright 2021 Zachary Selk
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
#include <Trundle/Core/layer.h>

namespace Trundle {

Layer::Layer(const std::string& name)
  : name(name) {}

Layer::~Layer() {}

void Layer::onAttach() {}

void Layer::onDetach() {}

void Layer::onUpdate() {}

void Layer::onEvent(Event&) {}

const std::string& Layer::getName() {
    return name;
}

} // namespace Trundle