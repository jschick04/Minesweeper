#pragma once

#include <cstdint>

namespace MineSweeper
{
    enum State : uint8_t
    {
        None,
        Revealed,
        Flagged,
        QuestionMark,
        Mine
    };
}
