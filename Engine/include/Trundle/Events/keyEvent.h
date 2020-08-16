//===-- keyEvent.h ---------------------------------------------------------===//
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
// Represents the components of an event from the keyboad.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Events/event.h>
#include <Trundle/Util/boilerplate.h>


namespace Trundle {

  //===-- KeyEvent ---------------------------------------------------------===//
  //
  // Contains information unique to a keyboard event.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API KeyEvent : public Event {
  public:
    int getKeyCode() const  { return keyCode; }

  protected:
    KeyEvent(int keyCode)
      : keyCode(keyCode)  { }

    int keyCode{-1};
  };


  //===-- KeyPressEvent ----------------------------------------------------===//
  //
  // An event for when a key on the keyboard is pressed down.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API KeyPressEvent : public KeyEvent {
  public:
    EVENT_BOILERPLATE(KeyPress);
    KeyPressEvent(int keyCode, bool repeatEvent)
      : KeyEvent(keyCode), repeatEvent(repeatEvent)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved KeyPressEvent with keyCode " << keyCode
         << " and is " << (repeatEvent ? "" : "not ") << "a repeated event";
      return ss.str();
    }

  private:
    bool repeatEvent = false;
  };


  //===-- KeyReleaseEvent --------------------------------------------------===//
  //
  // An event for when a key on the keyboard is released.
  //
  //===---------------------------------------------------------------------===//
  class TRUNDLE_API KeyReleaseEvent: public KeyEvent {
  public:
    EVENT_BOILERPLATE(KeyRelease);
    KeyReleaseEvent(int keyCode)
      : KeyEvent(keyCode)  { }

    std::string toString() const override final {
      std::stringstream ss;
      ss << "Recieved KeyReleaseEvent with keyCode " << keyCode;
      return ss.str();
    }
  };

}
