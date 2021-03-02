//===-- application.cpp ---------------------------------------------------===//
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
#include <Trundle/Core/application.h>
#include <Trundle/Core/log.h>
#include <Trundle/Events/windowEvent.h>

namespace Trundle {

Application* Application::instance = nullptr;

Application::Application(bool runHeadless)
  : headless(runHeadless) {
  instance = this;

  // Create a new window object.
  if (!headless) {
    window = Ref<Window>(Window::create());
    window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
  }
}

Application::~Application() {}

void Application::run() {
  while (running) {
    window->onUpdate();
  }
}

void Application::onEvent(Event &event) {
  EventDispatch dispatcher(event);
  dispatcher.dispatch<WindowCloseEvent>(
    [this](WindowCloseEvent &e)->bool { return onWindowClose(e); });

  if(!event.handled) {
    Log::Info(event.toString());
  }
}

bool Application::onWindowClose(WindowCloseEvent &event) {
  running = false;
  event.handled = true;
  return true;
}

} // namespace Trundle