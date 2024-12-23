#pragma once

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
        int m_cellHeight;
        int m_cellWidth;
        int m_columns = 12;
        bool m_isGameOver = false;
        int m_mines = 5;
        int m_rows = 12;
    };
}
