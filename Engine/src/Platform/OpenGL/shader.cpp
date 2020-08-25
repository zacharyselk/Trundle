//===-- shader.cpp ---------------------------------------------------------===//
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

#include <Trundle/Platform/OpenGL/shader.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


namespace Trundle::OpenGL {

    //===-- Shader ---------------------------------------------------------===//
    Shader::Shader(const std::string &vertexShader,
                   const std::string &fragmentShader)
        : id(glCreateProgram()) {
        uint32_t vs = compile(GL_VERTEX_SHADER, vertexShader);
        uint32_t fs = compile(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(id, vs);
        glAttachShader(id, fs);
        glLinkProgram(id);
        glValidateProgram(id);

        glDeleteShader(vs);
        glDeleteShader(fs);    
    }

    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::bind() const {
        glUseProgram(id);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    uint32_t Shader::compile(unsigned int type, const std::string &src) {
        unsigned int srcId = glCreateShader(type);
        const char* c_src = src.c_str();
        glShaderSource(srcId, 1, &c_src, NULL);
        glCompileShader(srcId);

        int result;
        glGetShaderiv(srcId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int len;
            glGetShaderiv(srcId, GL_INFO_LOG_LENGTH, &len);
            char* msg = new char[len];
            glGetShaderInfoLog(srcId, len, &len, msg);
            std::stringstream ss;
            ss << "Shader could not compile: " << msg;
            Log::Error(ss.str());
            exit(1);
        }

        return srcId;
    }

}