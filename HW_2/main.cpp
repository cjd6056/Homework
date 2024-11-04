#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Question 4
// Making a cool plot with openGL

// Function to draw Archimedean spiral
void drawArchimedeanSpiral(GLFWwindow* window) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    float scale = 0.02f; // Adjust the scale factor
    glBegin(GL_LINE_STRIP);
    for (float theta = 0.0f; theta <= 10.0f * 2 * 3.14159; theta += 0.01f) 
    {
        float radius = theta;
        float x = scale * radius * cos(theta);
        float y = scale * radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glfwSwapBuffers(window);
}

// Function to handle window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

int main() 
{
    // Initialize GLFW
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Archimedean Spiral", NULL, NULL);
    if (!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) 
    {
        // Render here
        drawArchimedeanSpiral(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

  return 0;
}