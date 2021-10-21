#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shaderLoader.h>
#include <window.h>

using std::cout, std::endl, std::string;


int main()
{
    cout << "(" << WIDTH << ", " << HEIGHT << ")" << endl;

    Window window = Window();

    window.window_loop();

    return 0;
}