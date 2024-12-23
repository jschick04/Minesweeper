#include "Cell.h"

#include "Colors.h"

namespace MineSweeper::Entities
{
    void Cell::Render(const int x, const int y, const int cellWidth, const int cellHeight) const
    {
        if (HasMine)
        {
            DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight, Colors::Red);
        }
        else if (AdjacentMines > 0)
        {
            DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight, Colors::White);
            DrawText(
                TextFormat("%d", AdjacentMines),
                x * cellWidth + 13,
                y * cellHeight + 4,
                cellHeight - 8,
                Colors::Black);
        }
        else
        {
            DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight, Colors::White);
        }
    }
}
