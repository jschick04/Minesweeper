#include "Grid.h"

#include "Colors.h"

namespace MineSweeper
{
    std::unique_ptr<Grid> Grid::Initialize(const int width, int const height)
    {
        return std::unique_ptr<Grid>(new Grid(width, height));
    }

    std::tuple<int, int> Grid::GetCellPosition(const Vector2& position) const
    {
        const int column = static_cast<int>(position.x) / m_cellWidth;
        const int row = static_cast<int>(position.y) / m_cellHeight;

        return IsValidCell(column, row) ? std::make_tuple(column, row) : std::make_tuple(0, 0);
    }

    bool Grid::IsComplete() const
    {
        return m_revealedCells == m_rows * m_columns - m_mines;
    }

    void Grid::Render() const
    {
        for (int x = 0; x < m_columns; x++)
        {
            for (int y = 0; y < m_rows; y++)
            {
                const auto& cell = m_grid[x * m_columns + y];

                if (cell.State == None)
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Grey);
                }
                else if (cell.State == Flagged)
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Green);
                }
                else if (cell.State == QuestionMark)
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Yellow);
                }
                else if (cell.State == Mine)
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Red);
                }
                else if (cell.AdjacentMines >= 0)
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::White);

                    if (cell.AdjacentMines > 0)
                    {
                        DrawText(
                            TextFormat("%d", cell.AdjacentMines),
                            x * m_cellWidth + 13,
                            y * m_cellHeight + 4,
                            m_cellHeight - 8,
                            Colors::Black);
                    }
                }
                else
                {
                    DrawRectangle(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::White);
                }

                DrawRectangleLines(x * m_cellWidth, y * m_cellHeight, m_cellWidth, m_cellHeight, Colors::Black);
            }
        }
    }

    void Grid::RevealAdjacentCells(const int column, const int row)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0) { continue; }

                const int xIndex = column + i;
                const int yIndex = row + j;

                if (xIndex >= 0 && xIndex < m_columns && yIndex >= 0 && yIndex < m_rows)
                {
                    const auto& cell = m_grid[xIndex * m_columns + yIndex];

                    if (cell.State != Revealed && cell.AdjacentMines == 0)
                    {
                        RevealCell(xIndex, yIndex);
                    }
                }
            }
        }
    }

    void Grid::RevealAllMines()
    {
        for (auto& cell : m_grid)
        {
            if (cell.HasMine)
            {
                cell.State = Mine;
            }
        }
    }

    State Grid::RevealCell(const int column, const int row)
    {
        if (!IsValidCell(column, row)) { return None; }

        Entities::Cell& cell = m_grid[column * m_columns + row];

        if (cell.State == Revealed) { return None; }

        if (cell.HasMine)
        {
            cell.State = Mine;

            return cell.State;
        }

        cell.State = Revealed;
        m_revealedCells++;

        if (cell.AdjacentMines == 0)
        {
            RevealAdjacentCells(column, row);
        }

        return cell.State;
    }

    void Grid::ToggleFlag(const int column, const int row)
    {
        if (!IsValidCell(column, row)) { return; }

        auto& cell = m_grid[column * m_columns + row];

        switch (cell.State)
        {
            case None:
                cell.State = Flagged;

                break;
            case Flagged:
                cell.State = QuestionMark;

                break;
            case QuestionMark:
                cell.State = None;

                break;
            case Revealed:
            case Mine:
            default:
                break;
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

    bool Grid::IsValidCell(const int column, const int row) const
    {
        return column >= 0 && column < m_columns && row >= 0 && row < m_rows;
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
