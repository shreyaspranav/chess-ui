#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

class Application 
{
public:
    Application(uint32_t width, uint32_t height, const char* title);
    ~Application();

    void Run();

private:
    void OnStart();
    void OnUpdate(double timestep);
    void OnExit();
private:
    GLFWwindow* m_Window;

    uint32_t m_Width, m_Height;
    std::string m_Title;
};