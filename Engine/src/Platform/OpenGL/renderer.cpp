//===-- renderer.h ---------------------------------------------------------===//
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

#include <Trundle/Platform/OpenGL/renderer.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle::OpenGL {

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Make not static.
        glClearColor(0.54, 0.17, 0.89, 1);
    }

    void Renderer::start() {
        // TODO
    }

    void Renderer::end() {
        while(!queue.empty()) {
            auto task = queue.front();
            task.array.bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            queue.pop();
        }
    }

    void Renderer::submit(const RenderingTask &task) {
        queue.push(task);
    }

}