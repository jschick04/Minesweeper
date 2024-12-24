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
        [[nodiscard]] std::tuple<int, int> GetCellPosition(const Vector2& position) const;
        [[nodiscard]] bool IsComplete() const;
        void Render() const;
        void RevealAdjacentCells(int column, int row);
        State RevealCell(int column, int row);
        void ToggleFlag(int column, int row);

    private:
        Grid(int width, int height);

    private:
        void CalculateAdjacentMines();
        [[nodiscard]] bool IsValidCell(int column, int row) const;
        void SetRandomMines();

    private:
        int m_cellHeight;
        int m_cellWidth;
        int m_columns = 12;
        std::vector<Entities::Cell> m_grid;
        int m_mines;
        int m_revealedCells = 0;
        int m_rows = 12;
    };
}
