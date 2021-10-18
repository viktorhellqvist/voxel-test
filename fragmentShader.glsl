// #version 330 core

// in vec3 outColor;

// out vec3 color;

// void main () {
//     color = outColor;
// }

#version 330 core

in vec3 color;
in vec2 texCoord;

uniform sampler2D noiseTexture;

void main()
{
    gl_FragColor = texture(noiseTexture, texCoord);
    // gl_FragColor = vec4(color, 1.0);
};