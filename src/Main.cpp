#include <iostream>

#include "Application.h"

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;
constexpr auto WINDOW_TITLE = "Chess UI";

int main() 
{


    Application* app = new Application(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    app->Run();
    delete app;

    return 0;
}