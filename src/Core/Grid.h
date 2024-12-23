#pragma once

#include <vector>

#include <Entities/Cell.h>

namespace MineSweeper
{
    class Grid
    {
    public:
        static Grid Initialize(int width, int height);

    public:
        void Render() const;

    private:
        Grid(int width, int height);

    private:
        void CalculateAdjacentMines();
        void SetRandomMines();

    private:
        int m_cellHeight;
        int m_cellWidth;
        int m_columns = 12;
        std::vector<Entities::Cell> m_grid;
        int m_mines;
        int m_rows = 12;
    };
}
