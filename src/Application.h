#pragma once

#include <memory>
#include <string>

#include "Game.h"

namespace MineSweeper
{
    struct ApplicationSpecification
    {
        std::string Title = "MineSweeper";
        int Width = 600;
        int Height = 600;
    };

    class Application
    {
    public:
        explicit Application(const ApplicationSpecification& spec = ApplicationSpecification());

        void OnRender() const;
        void OnUpdate() const;
        void Run();

    private:
        std::unique_ptr<Game> m_game;
        ApplicationSpecification m_spec;

    private:
        std::string m_gameOverText = "Game Over";
        std::string m_restartText = "Press Enter to restart";
        std::string m_winText = "You Win";
    };

    inline Application* CreateApplication()
    {
        return new Application();
    };
}
