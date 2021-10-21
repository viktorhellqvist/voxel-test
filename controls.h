#ifndef _controls_h_
#define _controls_h_

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: make position and stuff different from controls?

static const float moveSpeed = 3;
static const float mouseSpeed = 0.005;

/*
    Down is used to keep track if a key is currently pressed or not.
    Pressed tracks if the key was pressed during the current tick.
    So after every tick pressed is set to down's value.
    This means if a key is pressed and released in the same tick it is handled as if
    the key was pressed for all of the tick.
*/
struct Key
{
    bool down{};
    bool pressed{};
};

class Controls
{
public:
    Controls(GLFWwindow* _window, glm::vec3 startPos);

    void update_buttons();
    void update_mouse();

    glm::mat4 view();

    static Key keys[GLFW_KEY_LAST];

private:
    GLFWwindow* window;
    glm::vec3 position;
    float horizontalAngle = 3.14f / 0.8;
    float verticalAngle = -3.14f / 12;

    void tick_keys();
};

#endif /* _controls_h_ */