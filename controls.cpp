#ifndef _controls_
#define _controls_

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <controls.h>

using std::cout, std::endl;

const float tick_delta = 1.0f / 32;

Key Controls::keys[GLFW_KEY_LAST] = {};

Controls::Controls(GLFWwindow* _window, glm::vec3 startPos)
{
    window = _window;
    position = startPos;
    // TODO: Remove:
    assert(!keys[0].down && !keys[0].pressed);
    assert(!keys[1].down && !keys[1].pressed);
    assert(!keys[2].down && !keys[2].pressed);
    assert(!keys[3].down && !keys[3].pressed);
    assert(!keys[4].down && !keys[4].pressed);
}

void Controls::update_mouse()
{
    // TODO: Change these with #DEFINE's.
    int width = 1024, height = width * 3 / 4;

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // TODO: Add cursor callback?
    glfwSetCursorPos(window, width / 2, height / 2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * float(width / 2 - xpos);
    verticalAngle += mouseSpeed * float(height / 2 - ypos);

    // Limit up-down angel so camera can't flip
    if (verticalAngle > 3.14 / 2) verticalAngle = 3.14 / 2;
    else if (verticalAngle < -3.14 / 2) verticalAngle = -3.14 / 2;
}

void Controls::update_buttons()
{
    glm::vec3 lookDirection = {
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    };

    glm::vec3 rightDirection = {
        sin(horizontalAngle - 3.14f / 2),
        0,
        cos(horizontalAngle - 3.14f / 2)
    };

    glm::vec3 upDirection = glm::cross(rightDirection, lookDirection);
    if (keys[GLFW_KEY_W].pressed) {
        position += lookDirection * tick_delta * moveSpeed;
    }
    if (keys[GLFW_KEY_S].pressed) {
        position -= lookDirection * tick_delta * moveSpeed;
    }
    if (keys[GLFW_KEY_D].pressed) {
        position += rightDirection * tick_delta * moveSpeed;
    }
    if (keys[GLFW_KEY_A].pressed) {
        position -= rightDirection * tick_delta * moveSpeed;
    }

    tick_keys();
}

glm::mat4 Controls::view()
{
    glm::vec3 lookDirection = {
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
    };

    glm::vec3 rightDirection = {
        sin(horizontalAngle - 3.14f / 2),
        0,
        cos(horizontalAngle - 3.14f / 2)
    };

    glm::vec3 upDirection = glm::cross(rightDirection, lookDirection);

    return glm::lookAt(position, position + lookDirection, upDirection);
}

/**
 * Reset pressed value for all keys. Pressed is true if the key is currently held down, false otherwise.
 */
void Controls::tick_keys()
{
    for (int i = 0; i < GLFW_KEY_LAST; i++) {
        keys[i].pressed = keys[i].down;
    }
}

#endif /* _controls_ */