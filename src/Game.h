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
        [[nodiscard]] GameState CurrentState() const { return m_state; }

        [[nodiscard]] int GetPlayTime() const { return (m_endTime - m_startTime) % 60; }

        void OnRender() const;
        void OnUpdate();
        void Reset();

    private:
        Game(int width, int height);

        void HandleInput();

    private:
        int m_endTime = 0;
        std::unique_ptr<Grid> m_grid;
        int m_height;
        int m_startTime = 0;
        GameState m_state = MainMenu;
        int m_width;
    };
}
