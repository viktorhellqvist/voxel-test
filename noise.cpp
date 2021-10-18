#ifndef _noise_
#define _noise_

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include <noise.h>

// Hash lookup table as defined by Ken Perlin.  This is a randomly
// arranged array of all numbers from 0-255 inclusive.
static const int permutation[256] = { 151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

static int p[512];

glm::vec2 getConstantVec(int value)
{
    switch (value % 4) {
    case 0:
        return { 1.0f, 1.0f };
    case 1:
        return { -1.0f, 1.0f };
    case 2:
        return { 1.0f, -1.0f };
    default:
        return { -1.0f, -1.0f };
    }
}

float lerp(float x, float y, float t)
{
    return x + t * (y - x);
}

float ease(float v)
{
    return v * v * v * ((6 * v - 15) * v + 10);
}

void initPerlin()
{
    for (int i = 0; i < 512; i++) {
        p[i] = permutation[i % 256];
    }
}

float perlinNoise(float x, float y)
{
    int xi = static_cast<int>(x) % 256;
    int yi = static_cast<int>(y) % 256;

    // Position in square
    float xf = x - xi;
    float yf = y - yi;

    assert(xf < 1 && yf < 1);

    // Vectors from corner of cube to position
    glm::vec2 topRight{ xf - 1.0, yf - 1.0 };
    glm::vec2 topLeft{ xf, yf - 1.0 };
    glm::vec2 bottomRight{ xf - 1.0, yf };
    glm::vec2 bottomLeft{ xf, yf };

    float dotTopRight = glm::dot(topRight, getConstantVec(p[p[xi + 1] + yi + 1]));
    float dotTopLeft = glm::dot(topLeft, getConstantVec(p[p[xi] + yi + 1]));
    float dotBottomRight = glm::dot(bottomRight, getConstantVec(p[p[xi + 1] + yi]));
    float dotBottomLeft = glm::dot(bottomLeft, getConstantVec(p[p[xi] + yi]));

    float u = ease(xf);
    float v = ease(yf);

    float a = lerp(dotBottomLeft, dotTopLeft, v);
    float b = lerp(dotBottomRight, dotTopRight, v);
    return lerp(a, b, u);
}

#endif /* _noise_ */