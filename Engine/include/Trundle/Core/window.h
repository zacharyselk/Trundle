//===-- window.h -----------------------------------------------------------===//
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
// An abstract base class for the window provided by the OS. This abstraction
// needs to have a inherited implementation for each OS supported by Trundle.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Events/event.h>


namespace Trundle {

  struct WindowProperties {
    std::string title;
    uint32_t width, height;
    bool vSync{false};

  WindowProperties(uint32_t w=1280, uint32_t h=720,
                   const std::string &str="Trundle")
    : title(str), width(w), height(h)  { }
  };


  class Window {
  public:
    using eventCallback = std::function<void(Event&)>;

    virtual ~Window()  { }

    virtual void onUpdate() = 0;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;

    // Setting an event callback allows for events to be captured from the OS
    // without polling.
    virtual void setEventCallback(const eventCallback &callback) = 0;

    // V-Sync...because reasons I guess
    virtual void setVSync(bool enable) = 0;
    virtual bool isVSync() const = 0;

    // Returns a handle to the raw window object if needed
    virtual void* getNativeWindow() const = 0;

    static Window* create(const WindowProperties &properties=WindowProperties());
  };

}
