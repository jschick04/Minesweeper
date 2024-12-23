#pragma once

#include <memory>

#include "Grid.h"

namespace MineSweeper
{
    class Game
    {
    public:
        static Game Initialize(int width, int height);

    public:
        [[nodiscard]] bool IsGameOver() const;
        void OnRender() const;
        void OnUpdate();

    private:
        Game(int width, int height);

        void HandleInput();

    private:
        std::unique_ptr<Grid> m_grid;
        bool m_isGameOver = false;
    };
}
