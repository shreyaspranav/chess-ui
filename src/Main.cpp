#include <iostream>

#include "GLFW/glfw3.h"

int main() {
    int a = 0;

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Chess UI", nullptr, nullptr);
    glfwShowWindow(window);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}