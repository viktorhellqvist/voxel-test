// #version 330 core

// layout(location = 0) in vec3 vertexPosition;
// layout(location = 1) in vec3 vertexColor;

// out vec3 outColor;

// void main () {
//     gl_Position = vec4(vertexPosition, 1);
//     outColor = vertexColor;
// }


#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;

out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(vPos, 1.0);
    color = vCol;
    texCoord = vec2((vPos.x + 1) / 2, (vPos.y + 1) / 2);
}