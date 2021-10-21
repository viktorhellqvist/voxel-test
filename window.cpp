#ifndef _window_
#define _window_

#include <iostream>
#include <cmath>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shaderLoader.h>
#include <window.h>
#include <world.h>
#include <control.h>

using std::cout, std::endl, std::string;

static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << endl;
}

// TODO: move
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (action == GLFW_PRESS) {
        Controls::keys[key].down = true;
        Controls::keys[key].pressed = true;
    }
    else if (action == GLFW_RELEASE) {
        Controls::keys[key].down = false;
    }
}

Window::Window()
{
    if (!init(error_callback, key_callback)) {
        throw std::runtime_error("Failed to create glfw window");
    }
    controls = new Controls(window, { 4, 3, 5 });
}

bool Window::init(GLFWerrorfun error_callback, GLFWkeyfun key_callback)
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << endl;
        return false;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << endl;
        return false;
    }
    glfwMakeContextCurrent(window);

    // Init glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, key_callback);

    // Turn on mouse grab
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

    // TODO: glfwSetFrambufferSizeCallback to allow for window resizing
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    // Enable depth test and set less as depth function.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    // Create VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    shaderID = Shader("vertexShader.glsl", "fragmentShader.glsl").ID;
    glUseProgram(shaderID);
    glClearColor(0.0f, 0.4f, 0.4f, 0.0f);

    loadVertices();
    loadColors();

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    GLuint colorBufferID;
    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

    return true;
}

void Window::window_loop()
{

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    GLuint colorBufferID;
    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

    auto mvp = loadMVP();
    GLint mvpID = glGetUniformLocation(shaderID, "mvp");

    const double tickTime = 1.0 / 32;
    static double lastTick = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        if (glfwGetTime() - lastTick > tickTime) {
            controls->update_buttons();
            lastTick = glfwGetTime();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderID);

        mvp = loadMVP();
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
        controls->update_mouse();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::loadVertices()
{
    vertices = getCube(0, 0, 0);
    auto tmp = getCube(1, 0, 0);
    vertices.insert(vertices.end(), tmp.begin(), tmp.end());

    tmp = getCube(0, 0, 2);
    vertices.insert(vertices.end(), tmp.begin(), tmp.end());
}

void Window::loadColors()
{
    std::vector<glm::vec3> tmp = {
        {0.583f,  0.771f,  0.014f},
        {0.609f,  0.115f,  0.436f},
        {0.327f,  0.483f,  0.844f},
        {0.822f,  0.569f,  0.201f},
        {0.435f,  0.602f,  0.223f},
        {0.310f,  0.747f,  0.185f},
        {0.597f,  0.770f,  0.761f},
        {0.559f,  0.436f,  0.730f},
        {0.359f,  0.583f,  0.152f},
        {0.483f,  0.596f,  0.789f},
        {0.559f,  0.861f,  0.639f},
        {0.195f,  0.548f,  0.859f},
        {0.014f,  0.184f,  0.576f},
        {0.771f,  0.328f,  0.970f},
        {0.406f,  0.615f,  0.116f},
        {0.676f,  0.977f,  0.133f},
        {0.971f,  0.572f,  0.833f},
        {0.140f,  0.616f,  0.489f},
        {0.997f,  0.513f,  0.064f},
        {0.945f,  0.719f,  0.592f},
        {0.543f,  0.021f,  0.978f},
        {0.279f,  0.317f,  0.505f},
        {0.167f,  0.620f,  0.077f},
        {0.347f,  0.857f,  0.137f},
        {0.055f,  0.953f,  0.042f},
        {0.714f,  0.505f,  0.345f},
        {0.783f,  0.290f,  0.734f},
        {0.722f,  0.645f,  0.174f},
        {0.302f,  0.455f,  0.848f},
        {0.225f,  0.587f,  0.040f},
        {0.517f,  0.713f,  0.338f},
        {0.053f,  0.959f,  0.120f},
        {0.393f,  0.621f,  0.362f},
        {0.673f,  0.211f,  0.457f},
        {0.820f,  0.883f,  0.371f},
        {0.982f,  0.099f,  0.879f}
    };

    std::vector<glm::vec3> gray = {
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
        {0.50f, 0.50f, 0.50f},
        {0.55f, 0.55f, 0.55f},
        {0.45f, 0.45f, 0.45f},
    };

    std::vector<glm::vec3> green = {
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
        {0.3f, 0.5f, 0.2f},
        {0.35f, 0.55f, 0.25f},
        {0.25f, 0.45f, 0.15f},
    };

    colors.insert(colors.end(), green.begin(), green.end());
    colors.insert(colors.end(), gray.begin(), gray.end());
    colors.insert(colors.end(), gray.begin(), gray.end());
}

void printMat4(glm::mat4& mat)
{
    cout << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", " << mat[0][3] << endl;
    cout << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", " << mat[1][3] << endl;
    cout << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ", " << mat[2][3] << endl;
    cout << mat[3][0] << ", " << mat[3][1] << ", " << mat[3][2] << ", " << mat[3][3] << endl;
}

glm::mat4 Window::loadMVP()
{
    // TODO: Display range
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = controls->view();

    glm::mat4 view2 = glm::lookAt(glm::vec3(4.0f, 3.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    return projection * view;
}


#endif /* _window_ */