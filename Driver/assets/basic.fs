#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_position;
in vec4 v_color;
void main(){
    color = v_color;
}