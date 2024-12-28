#include "Game.h"

namespace MineSweeper
{
    std::unique_ptr<Game> Game::Initialize(const int width, const int height)
    {
        return std::unique_ptr<Game>(new Game(width, height));
    }

    void Game::OnRender() const
    {
        m_grid->Render();
    }

    void Game::OnUpdate()
    {
        HandleInput();
    }

    void Game::Reset()
    {
        m_grid = Grid::Initialize(m_width, m_height);
        m_startTime = GetTime();
        m_state = Playing;
    }

    Game::Game(const int width, const int height) : m_height(height), m_width(width) { }

    void Game::HandleInput()
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            const auto [column, row] = m_grid->GetCellPosition(GetMousePosition());

            const State state = m_grid->RevealCell(column, row);

            if (state == Mine)
            {
                m_grid->RevealAllMines();

                m_endTime = GetTime();
                m_state = Lose;
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            const auto [column, row] = m_grid->GetCellPosition(GetMousePosition());

            m_grid->ToggleFlag(column, row);
        }

        if (m_grid->IsComplete())
        {
            m_endTime = GetTime();
            m_state = Win;
        }
    }
}
