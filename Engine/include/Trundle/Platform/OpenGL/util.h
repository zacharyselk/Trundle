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
// Helper functions for the OpenGL rendering backend.
//
//===-----------------------------------------------------------------------===//

#pragma once

#include <Trundle/common.h>
#include <Trundle/Render/util.h>


namespace Trundle::OpenGL {

    static GLenum toOpenGL(const Trundle::Rendering::GraphicsType &type) {
        switch (type) {
        case Trundle::Rendering::Float:
        case Trundle::Rendering::Float2:
        case Trundle::Rendering::Float3:
        case Trundle::Rendering::Float4:
            return GL_FLOAT;
        }

        Log::Error("Unknown GraphicsType");
        exit(1);
        return (GLenum)-1; 
    }

}