#pragma once

#include <State.h>

namespace MineSweeper::Entities
{
    struct Cell
    {
        int AdjacentMines = 0;
        bool HasMine = false;
        State State = None;
    };
}
