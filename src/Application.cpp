#include "Application.h"

#include "Colors.h"

namespace MineSweeper
{
    // ReSharper disable once CppPossiblyUninitializedMember
    // m_font has to be initialized after InitWindow
    Application::Application(const ApplicationSpecification& spec) : m_spec(spec) { }

    void Application::OnRender() const
    {
        BeginDrawing();
        ClearBackground(Colors::White);

        m_game->OnRender();

        if (m_game->IsGameOver()) { }

        EndDrawing();
    }

    void Application::OnUpdate() const
    {
        m_game->OnUpdate();
    }

    void Application::Run()
    {
        InitWindow(m_spec.Width, m_spec.Height, m_spec.Title.c_str());
        SetTargetFPS(60);

        m_game = std::make_unique<Game>(Game::Initialize(m_spec.Width, m_spec.Height));

        while (!WindowShouldClose())
        {
            OnUpdate();
            OnRender();
        }

        CloseWindow();
    }
}
