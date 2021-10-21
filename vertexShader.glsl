#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;

uniform mat4 mvp;

out vec3 color;

void main()
{
    gl_Position = mvp * vec4(vPos, 1.0);
    color = vCol;
}