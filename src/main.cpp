#include "Application.h"

int main()
{
    MineSweeper::Application* app = MineSweeper::CreateApplication();

    app->Run();

    delete app;
}
