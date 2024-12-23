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

    void Game::HandleInput() { }
}
