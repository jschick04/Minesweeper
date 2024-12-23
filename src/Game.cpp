#include "Game.h"

namespace MineSweeper
{
    Game Game::Initialize(const int width, const int height)
    {
        return { width, height };
    }

    bool Game::IsGameOver() const { return m_isGameOver; }

    void Game::OnRender() const { }

    void Game::OnUpdate()
    {
        if (m_isGameOver) { return; }

        HandleInput();
    }

    Game::Game(const int width, const int height)
    {
        m_cellHeight = height / m_columns;
        m_cellWidth = width / m_columns;
    }

    void Game::HandleInput() { }
}
