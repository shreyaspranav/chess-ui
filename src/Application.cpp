#include "Application.h"

#include <iostream>

#include "Renderer.h"

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include "GLFW/glfw3.h"

float board_x_offset = 0.6f;

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
    Renderer::Init();
    m_Pieces = new ChessPieces("");
}

void Application::OnUpdate(double timestep)
{
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(m_Window, &windowWidth, &windowHeight);

    Renderer::Begin(windowWidth, windowHeight);

    Application::RenderChessBoard();
    Application::RenderChessPieces();

    Renderer::RenderFrame();
}

void Application::OnExit()
{
    delete m_Pieces;

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::RenderChessBoard()
{
    glm::vec4 dark_square_color = {0.0f, 0.4f, 0.0f, 1.0f};
    glm::vec4 light_square_color = {1.0f, 0.9921f, 0.8156f, 1.0f};

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i % 2 == j % 2)
                Renderer::DrawQuad({-0.7f + board_x_offset + (i * 0.2f), -0.7f + (j * 0.2f), 0.0f}, 0.0f, {0.2f, 0.2f}, dark_square_color);
            else
                Renderer::DrawQuad({-0.7f + board_x_offset + (i * 0.2f), -0.7f + (j * 0.2f), 0.0f}, 0.0f, {0.2f, 0.2f}, light_square_color);
        }
    }
}

void Application::RenderChessPieces()
{
    for(const auto& piece : m_Pieces->GetChessPiecesMap())
    {

    }
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
        glClearColor(0.2f, 0.2f ,0.2f, 1.0f);

        Application::OnUpdate(0.0);

        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}
