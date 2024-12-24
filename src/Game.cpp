#include "Game.h"

namespace MineSweeper
{
    Game Game::Initialize(const int width, const int height)
    {
        return { width, height };
    }

    bool Game::IsGameOver() const { return m_isGameOver; }

    void Game::OnRender() const
    {
        m_grid->Render();
    }

    void Game::OnUpdate()
    {
        if (m_isGameOver) { return; }

        HandleInput();
    }

    Game::Game(const int width, const int height)
    {
        m_grid = std::make_unique<Grid>(Grid::Initialize(width, height));
    }

    void Game::HandleInput()
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            const auto [column, row] = m_grid->GetCellPosition(GetMousePosition());

            const State state = m_grid->RevealCell(column, row);

            if (state == Mine)
            {
                m_isGameOver = true;
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            const auto [column, row] = m_grid->GetCellPosition(GetMousePosition());

            m_grid->ToggleFlag(column, row);
        }

        if (m_grid->IsComplete())
        {
            // TODO: Set win condition
            m_isGameOver = true;
        }
    }
}
