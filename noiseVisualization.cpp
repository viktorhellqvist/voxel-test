#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include <shaderLoader.h>
#include <noise.h>

using std::cout, std::endl, std::string;

static int WIDTH = 1024;
static int HEIGHT = WIDTH * 3 / 4;

static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GLFWwindow* init()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << endl;
        return NULL;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << endl;
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // Init glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, key_callback);

    // TODO: glfwSetFrambufferSizeCallback to allow for window resizing
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    return window;
}

// Returns the new texture ID
GLuint genTexture(GLuint shaderID, const char* name)
{
    initPerlin();
    int texWidth = 300, texHeight = 300;
    float picData[texWidth * texHeight * 3];

    int midWidth = texWidth / 2;
    int midHeight = texHeight / 2;
    int scale = midWidth * midWidth + midHeight * midHeight;

    for (int y = 0; y < texHeight; y++) {
        for (int x = 0; x < texWidth; x++) {
            float xf = x;
            float yf = y;
            float value = perlinNoise(xf * 0.03, yf * 0.03);
            value = (value + 1) / 2;
            picData[y * 3 * texWidth + (x * 3)] = value;
            picData[y * 3 * texWidth + (x * 3 + 1)] = value;
            picData[y * 3 * texWidth + (x * 3 + 2)] = value;
        }
    }

    // GLuint textureID = glGetUniformLocation(shaderID, name);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Texture paramaters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_FLOAT, picData);

    auto location = glGetUniformLocation(shaderID, name);
    if (location == -1) {
        std::cerr << "Could not find uniform locaion of \"" << name << "\"" << endl;
        return -1;
    }
    glUniform1i(location, 0);

    return textureID;
}

int main(void)
{
    GLFWwindow* window = init();
    if (window == NULL) {
        glfwTerminate();
        return 0;
    }

    // Create VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    const GLuint nrVertices = 6;
    glm::vec3 vertices[nrVertices] = {
        {1.0f, 1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f}
    };

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, nrVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

    Shader shader = Shader("noiseVertexShader.glsl", "noiseFragmentShader.glsl");
    glUseProgram(shader.ID);
    glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
    cout << "HeJ" << endl;

    auto textureID = genTexture(shader.ID, "noiseTexture");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader.ID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, nrVertices);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}