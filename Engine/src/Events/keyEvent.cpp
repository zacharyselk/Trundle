//===-- keyEvent.cpp ------------------------------------------------------===//
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
#include <Trundle/Events/keyEvent.h>

namespace Trundle {

//===-- KeyEvent ----------------------------------------------------------===//
KeyEvent::KeyEvent(int keyCode) : keyCode(keyCode) {}

int KeyEvent::getKeyCode() const { return keyCode; }
//===----------------------------------------------------------------------===//

//===-- KeyPressEvent -----------------------------------------------------===//
KeyPressEvent::KeyPressEvent(int keyCode, bool repeatEvent)
    : KeyEvent(keyCode), repeatEvent(repeatEvent) {}

EventType KeyPressEvent::getStaticType() { return EventType::KeyPress; }

EventType KeyPressEvent::getEventType() const { return getStaticType(); }

const char* KeyPressEvent::getName() const { return "KeyPress"; }

std::string KeyPressEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved KeyPressEvent with keyCode " << keyCode << " and is "
     << (repeatEvent ? "" : "not ") << "a repeated event";
  return ss.str();
}
//===----------------------------------------------------------------------===//

//===-- KeyReleaseEvent ---------------------------------------------------===//
KeyReleaseEvent::KeyReleaseEvent(int keyCode) : KeyEvent(keyCode) {}

EventType KeyReleaseEvent::getStaticType() { return EventType::KeyRelease; }

EventType KeyReleaseEvent::getEventType() const { return getStaticType(); }

const char* KeyReleaseEvent::getName() const { return "Key Release"; }

std::string KeyReleaseEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved KeyReleaseEvent with keyCode " << keyCode;
  return ss.str();
}
//===----------------------------------------------------------------------===//

} // namespace Trundle