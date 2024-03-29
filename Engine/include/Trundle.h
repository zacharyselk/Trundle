//===-- Trundle.h ---------------------------------------------------------===//
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
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// Provides an interface between the client driver code and the engine API.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <Trundle/Core/gateway.h>
#include <Trundle/Core/keyCode.h>
#include <Trundle/Core/log.h>
#include <Trundle/Core/pointer.h>
#include <Trundle/Events/event.h>
#include <Trundle/Events/keyEvent.h>
#include <Trundle/Events/mouseEvent.h>
#include <Trundle/Events/windowEvent.h>