#version 330 core

layout(location = 0) in vec3 vPos;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    texCoord = vec2((vPos.x + 1) / 2, (vPos.y + 1) / 2);
}