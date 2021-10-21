#version 330 core

in vec2 texCoord;

uniform sampler2D noiseTexture;

void main()
{
    gl_FragColor = texture(noiseTexture, texCoord);
};