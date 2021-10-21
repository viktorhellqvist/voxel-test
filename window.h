#ifndef _window_h_
#define _window_h_

#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shaderLoader.h>
#include <controls.h>

#define WIDTH 1024
#define HEIGHT WIDTH * 3 / 4

class Window
{
public:
    Window();

    void window_loop();

private:
    bool init(GLFWerrorfun error_callback, GLFWkeyfun key_callback);
    void loadVertices();
    void loadColors();
    glm::mat4 loadMVP();

    GLFWwindow* window;
    Controls* controls;
    int shaderID;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
};

#endif /* _window_h_ */