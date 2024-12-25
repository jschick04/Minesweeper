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

        const char* playTimeText;

        switch (m_game->CurrentState())
        {
            case MainMenu:
                DrawText("MineSweeper", 20, 20, 60, Colors::Black);
                DrawText("Main Menu", 40, 150, 30, Colors::Black);
                DrawText("New Game", 40, 210, 20, Colors::Black);
                DrawText("Options", 40, 230, 20, Colors::Black);
                DrawText("Exit", 40, 250, 20, Colors::Black);

                break;
            case OptionsMenu:
                DrawText("MineSweeper", 20, 20, 60, Colors::Black);
                DrawText("Options", 40, 150, 30, Colors::Black);

                break;
            case Playing:
                m_game->OnRender();

                break;
            case Win:
                m_game->OnRender();

                DrawRectangle(0, 0, m_spec.Width, m_spec.Height, Fade(Colors::White, 0.8f));

                DrawText(m_winText.c_str(),
                    m_spec.Width / 2 - MeasureText(m_winText.c_str(), 60) / 2,
                    m_spec.Height / 2 - 50,
                    60,
                    Colors::Black);

                DrawText(m_restartText.c_str(),
                    m_spec.Width / 2 - MeasureText(m_restartText.c_str(), 20) / 2,
                    m_spec.Height / 2 + 10,
                    20,
                    Colors::Black);

                playTimeText = TextFormat("Time Played: %d s", m_game->GetPlayTime());
                DrawText(playTimeText,
                    m_spec.Width / 2 - MeasureText(playTimeText, 30) / 2,
                    m_spec.Height / 4,
                    30,
                    Colors::Black);

                break;
            case Lose:
                m_game->OnRender();

                DrawRectangle(0, 0, m_spec.Width, m_spec.Height, Fade(Colors::White, 0.8f));

                DrawText(m_gameOverText.c_str(),
                    m_spec.Width / 2 - MeasureText(m_gameOverText.c_str(), 60) / 2,
                    m_spec.Height / 2 - 50,
                    60,
                    Colors::Black);

                DrawText(m_restartText.c_str(),
                    m_spec.Width / 2 - MeasureText(m_restartText.c_str(), 20) / 2,
                    m_spec.Height / 2 + 10,
                    20,
                    Colors::Black);

                playTimeText = TextFormat("Time Played: %d s", m_game->GetPlayTime());
                DrawText(playTimeText,
                    m_spec.Width / 2 - MeasureText(playTimeText, 30) / 2,
                    m_spec.Height / 4,
                    30,
                    Colors::Black);

                break;
        }

        EndDrawing();
    }

    void Application::OnUpdate() const
    {
        switch (m_game->CurrentState())
        {
            case MainMenu:
                if (IsKeyPressed(KEY_ENTER))
                {
                    m_game->Reset();
                }

                break;
            case OptionsMenu:
                break;
            case Playing:
                m_game->OnUpdate();

                break;
            case Win:
            case Lose:
                if (IsKeyPressed(KEY_ENTER))
                {
                    m_game->Reset();
                }

                break;
        }
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
