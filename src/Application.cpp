#include "Application.h"

#include <iostream>

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include "GLFW/glfw3.h"

Application::Application(uint32_t width, uint32_t height, const char* title)
    :m_Width(width), m_Height(height), m_Title(title)
{
    if(!glfwInit())
        std::cerr << "ERROR INITIALIZING GLFW!\n";
}

Application::~Application()
{
    Application::OnExit();
}

void Application::OnStart()
{
    
}

void Application::OnUpdate(double timestep)
{
   
}

void Application::OnExit()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Run()
{
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    glfwShowWindow(m_Window);
    glfwSwapInterval(1);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_Window, (mode->width - m_Width) / 2, (mode->height - m_Height) / 2);

    glfwMakeContextCurrent(m_Window);
    int version = gladLoadGL(glfwGetProcAddress);
    if(version == 0)
        std::cerr << "Error Loading OpenGL library!\n";

    Application::OnStart();

    while (!glfwWindowShouldClose(m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f ,0.0f, 1.0f);

        Application::OnUpdate(0.0);

        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}
