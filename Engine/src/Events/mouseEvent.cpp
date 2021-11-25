//===-- mouseEvent.cpp ----------------------------------------------------===//
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
#include <Trundle/Events/mouseEvent.h>

namespace Trundle {

//===-- MouseButtonEvent --------------------------------------------------===//
MouseButtonEvent::MouseButtonEvent(int mouseCode) : mouseCode(mouseCode) {}

int MouseButtonEvent::getMouseCode() const { return mouseCode; }
//===----------------------------------------------------------------------===//

//===-- MousePressEvent ---------------------------------------------------===//
MousePressEvent::MousePressEvent(int mouseCode) : MouseButtonEvent(mouseCode) {}

EventType MousePressEvent::getStaticType() { return EventType::MousePress; }

EventType MousePressEvent::getEventType() const { return getStaticType(); }

const char* MousePressEvent::getName() const { return "MousePress"; }

std::string MousePressEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved MousePressEvent with mouseCode " << mouseCode;
  return ss.str();
}
//===----------------------------------------------------------------------===//

//===-- MouseReleaseEvent
//---------------------------------------------------===//
MouseReleaseEvent::MouseReleaseEvent(int mouseCode)
    : MouseButtonEvent(mouseCode) {}

EventType MouseReleaseEvent::getStaticType() { return EventType::MouseRelease; }

EventType MouseReleaseEvent::getEventType() const { return getStaticType(); }

const char* MouseReleaseEvent::getName() const { return "MouseRelease"; }

std::string MouseReleaseEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved MouseReleaseEvent with mouseCode " << mouseCode;
  return ss.str();
}
//===----------------------------------------------------------------------===//

//===-- MouseMoveEvent ----------------------------------------------------===//
MouseMoveEvent::MouseMoveEvent(double x, double y) : x(x), y(y) {}

EventType MouseMoveEvent::getStaticType() { return EventType::MouseMove; }

EventType MouseMoveEvent::getEventType() const { return getStaticType(); }

const char* MouseMoveEvent::getName() const { return "MouseMove"; }

std::string MouseMoveEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved MouseMoveEvent at position (" << x << ", " << y << ")";
  return ss.str();
}

std::tuple<double, double> MouseMoveEvent::getPosition() const {
  return {x, y};
}
//===----------------------------------------------------------------------===//

} // namespace Trundle