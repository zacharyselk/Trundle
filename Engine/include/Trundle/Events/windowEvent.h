//===-- windowEvent.h ------------------------------------------------------===//
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
// Represents the components of an event from the window.
//
//===-----------------------------------------------------------------------===//

#pragma once


#include <Trundle/common.h>
#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>

namespace Trundle {

  //===-- WindowCloseEvent -------------------------------------------------===//
  //
  // An event for when a window is closed.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API WindowCloseEvent : public Event {
  public:
    EVENT_BOILERPLATE(WindowClose);
    WindowCloseEvent()  { }

    std::string toString() const override final {
      return std::string("Recieved WindowCloseEvent");
    }
  };


  //===-- WindowResizeEvent ------------------------------------------------===//
  //
  // An event for when a window is resized.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API WindowResizeEvent : public Event {
  public:
    EVENT_BOILERPLATE(WindowResize);
    WindowResizeEvent(int w, int h)
      : width(w), height(h)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved WindowResizeEvent with dimensions " << width
         << "x" << height;
      return ss.str();
    }

  private:
    int width{-1};
    int height{-1};
  };

}
