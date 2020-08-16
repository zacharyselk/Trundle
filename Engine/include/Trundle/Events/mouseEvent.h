//===-- mouseEvent.h -------------------------------------------------------===//
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
// Represents the components of an event from the mouse.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>


namespace Trundle {

  //===-- MouseMoveEvent ---------------------------------------------------===//
  //
  // An event that represents when the mouse has moved.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API MouseMoveEvent : public Event {
  public:
    EVENT_BOILERPLATE(MouseMove);
    MouseMoveEvent(double x, double y)
      : x(x), y(y)  { }

    std::tuple<int, int> getPos() const  { return std::make_tuple(x, y); }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MouseMoveEvent at position (" << x
         << ", " << y << ")";
      return ss.str();
    }

  private:
    double x = 0;
    double y = 0;
  };

  class TRUNDLE_API MouseButtonEvent : public Event {
  public:
    int getMouseCode() const  { return mouseCode; }

  protected:
    MouseButtonEvent(int mouseCode)
      : mouseCode(mouseCode)  { }

    int mouseCode{-1};
  };


  //===-- MousePressEvent --------------------------------------------------===//
  //
  // An event that represents when a mouse button has been clicked.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API MousePressEvent : public MouseButtonEvent {
  public:
    EVENT_BOILERPLATE(MousePress);
    MousePressEvent(int mouseCode)
      : MouseButtonEvent(mouseCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MousePressEvent with mouseCode " << mouseCode;
      return ss.str();
    }
  };


  //===-- MouseReleaseEvent ------------------------------------------------===//
  //
  // An event that represents when a mouse button has been released.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API MouseReleaseEvent: public MouseButtonEvent {
  public:
    EVENT_BOILERPLATE(MouseRelease);
    MouseReleaseEvent(int mouseCode)
      : MouseButtonEvent(mouseCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved MouseReleaseEvent with mouseCode " << mouseCode;
      return ss.str();
    }
  };

}
