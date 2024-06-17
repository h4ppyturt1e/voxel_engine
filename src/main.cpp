#include "main.h"

// Global variables
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;
unsigned int shaderProgram;
unsigned int edgeShaderProgram;
unsigned int projectionLoc;
unsigned int viewLoc;
unsigned int modelLoc;
glm::mat4 projection;
bool useEdgeShader = false;

Player player(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), SCR_WIDTH, SCR_HEIGHT);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
void updateProjectionMatrix(int width, int height);

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "Failed to initialize GLFW: " << description << " (code " << code << ")" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr)
    {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "Failed to create GLFW window: " << description << " (code " << code << ")" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create a block
    Block block(glm::vec3(0.0f, 0.0f, 0.0f), BlockType::Grass);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, block.getVertices().size() * sizeof(float), block.getVertices().data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load shaders from files
    std::string vertexShaderSource = readFile("../shaders/vertex_shader.glsl");
    std::string fragmentShaderSource = readFile("../shaders/fragment_shader.glsl");

    shaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    std::string edgeVertexShaderSource = readFile("../shaders/edge_vertex_shader.glsl");
    std::string edgeFragmentShaderSource = readFile("../shaders/edge_fragment_shader.glsl");

    edgeShaderProgram = createShaderProgram(edgeVertexShaderSource.c_str(), edgeFragmentShaderSource.c_str());

    // Use shader program
    glUseProgram(shaderProgram);

    // Get the uniform locations
    projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    modelLoc = glGetUniformLocation(shaderProgram, "model");

    // Set up the initial projection matrix
    updateProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Render loop
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, deltaTime);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update view matrix
        glm::mat4 view = player.getViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Transformation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, block.getPosition());

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);

        // Render the object with regular shader
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Render the edges if the edge shader is active
        if (useEdgeShader) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen again
            glUseProgram(edgeShaderProgram);
            glUniformMatrix4fv(glGetUniformLocation(edgeShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(edgeShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(edgeShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(3.0f);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(edgeShaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    updateProjectionMatrix(width, height);
}

void updateProjectionMatrix(int width, int height)
{
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(edgeShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(edgeShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void processInput(GLFWwindow* window, float deltaTime)
{
    player.processInput(window, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool pPressed = false;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pPressed) {
        useEdgeShader = !useEdgeShader;
        pPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
        pPressed = false;
    }
}
