#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Player {
public:
    Player(glm::vec3 startPosition, glm::vec3 up, unsigned int screenWidth, unsigned int screenHeight);

    void processInput(GLFWwindow *window, float deltaTime);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float gravity;

    unsigned int screenWidth;
    unsigned int screenHeight;

    void updateCameraVectors();
};

#endif // PLAYER_H