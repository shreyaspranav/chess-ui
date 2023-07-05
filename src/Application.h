#pragma once

#include <cstdint>
#include <string>

#include "ChessPieces.h"

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

    void RenderChessBoard();
    void RenderChessPieces();
private:
    GLFWwindow* m_Window;

    uint32_t m_Width, m_Height;
    std::string m_Title;

    ChessPieces* m_Pieces;
};