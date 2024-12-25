#pragma once

#include <memory>
#include <string>

#include "Game.h"

namespace MineSweeper
{
    struct ApplicationSpecification
    {
        int Height = 600;
        int Width = 600;
        std::string Title = "MineSweeper";
    };

    class Application
    {
    public:
        explicit Application(const ApplicationSpecification& spec = ApplicationSpecification());
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;
        ~Application() noexcept = default;

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
}
