#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Rendering code here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}