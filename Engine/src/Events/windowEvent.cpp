//===-- windowEvent.cpp ----------------------------------------------------===//
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
#include <Trundle/Events/windowEvent.h>

namespace Trundle {

//===-- WindowCloseEvent ---------------------------------------------------===//
WindowCloseEvent::WindowCloseEvent() {}

EventType WindowCloseEvent::getStaticType() { 
  return EventType::WindowClose;
}

EventType WindowCloseEvent::getEventType() const { 
  return getStaticType();
}

const char* WindowCloseEvent::getName() const { 
  return "WindowClose";
}

std::string WindowCloseEvent::toString() const {
  return std::string("Recieved WindowCloseEvent");
}
//===----------------------------------------------------------------------===//


//===-- WindowResizeEvent ---------------------------------------------------===//
WindowResizeEvent::WindowResizeEvent(int w, int h)
: width(w), height(h) {}

EventType WindowResizeEvent::getStaticType() { 
  return EventType::WindowResize;
}

EventType WindowResizeEvent::getEventType() const { 
  return getStaticType();
}

const char* WindowResizeEvent::getName() const { 
  return "WindowResize";
}

std::string WindowResizeEvent::toString() const {
  // TODO: Replace with something better than a stringstream.
  std::stringstream ss;
  ss << "Recieved WindowResizeEvent with dimensions " << width << "x"
     << height;
  return ss.str();
}
//===----------------------------------------------------------------------===//

} // namespace Trundle