#include "Grid.h"

#include "Colors.h"

namespace MineSweeper
{
    Grid Grid::Initialize(int width, int height)
    {
        return { width, height };
    }

    void Grid::Render() const
    {
        for (int x = 0; x < m_columns; x++)
        {
            for (int y = 0; y < m_rows; y++)
            {
                m_grid[x * m_columns + y].Render(x, y, m_cellWidth, m_cellHeight);

                DrawRectangleLines(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Black);
            }
        }
    }

    Grid::Grid(const int width, const int height)
    {
        m_cellHeight = height / m_columns;
        m_cellWidth = width / m_columns;

        m_grid.resize(m_rows * m_columns);

        m_mines = m_rows * m_columns * 0.1f;

        SetRandomMines();
        CalculateAdjacentMines();
    }

    void Grid::CalculateAdjacentMines()
    {
        for (int x = 0; x < m_columns; x++)
        {
            for (int y = 0; y < m_rows; y++)
            {
                auto& cell = m_grid[x * m_columns + y];

                if (cell.HasMine) { continue; }

                int adjacentMines = 0;

                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i == 0 && j == 0) { continue; }

                        const int xIndex = x + i;
                        const int yIndex = y + j;

                        if (xIndex >= 0 && xIndex < m_columns && yIndex >= 0 && yIndex < m_rows)
                        {
                            if (m_grid[xIndex * m_columns + yIndex].HasMine)
                            {
                                adjacentMines++;
                            }
                        }
                    }
                }

                cell.AdjacentMines = adjacentMines;
            }
        }
    }

    void Grid::SetRandomMines()
    {
        int remainingMines = m_mines;

        while (remainingMines > 0)
        {
            const int x = GetRandomValue(0, m_columns - 1);
            const int y = GetRandomValue(0, m_rows - 1);

            auto& cell = m_grid[x * m_columns + y];

            if (cell.HasMine) { continue; }

            cell.HasMine = true;
            remainingMines--;
        }
    }
}
