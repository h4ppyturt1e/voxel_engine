#ifndef MAIN_H
#define MAIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader_utils.h"
#include "objects/Block.h"
#include "objects/Player.h"

// Global variables
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;
extern unsigned int shaderProgram;
extern unsigned int projectionLoc;
extern unsigned int viewLoc;

extern Player player;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
void updateProjectionMatrix(int width, int height);

#endif // MAIN_H
