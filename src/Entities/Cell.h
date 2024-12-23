#pragma once

#include <State.h>

namespace MineSweeper::Entities
{
    class Cell
    {
    public:
        void Render(int x, int y, int cellWidth, int cellHeight) const;

    public:
        int AdjacentMines = 0;
        bool HasMine = false;
        State State = None;
    };
}
