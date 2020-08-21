//===-- util.h -------------------------------------------------------------===//
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
// Rendering API helper functions.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Core/log.h>

//#include <GL/gl3w.h>
//#include <GLFW/glfw3.h>


namespace Trundle::Rendering {

    enum GraphicsType {
        None=0,
        Float,
        Float2,
        Float3,
        Float4
    };


    static uint32_t getSizeOf(const GraphicsType &type) {
        switch (type) {
        case Float:
            return 4;
        case Float2:
            return 4*2;
        case Float3:
            return 4*3;
        case Float4:
            return 4*4;
        }

        Log::Error("Unknown GraphicsType");
        exit(1);
        return -1;
    }

        static uint32_t getComponentSizeOf(const GraphicsType &type) {
        switch (type) {
        case Float:
        case Float2:
        case Float3:
        case Float4:
            return 4;
        }

        Log::Error("Unknown GraphicsType");
        exit(1);
        return -1;
    }

}