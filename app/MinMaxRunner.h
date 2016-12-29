#pragma once

#include <vector>

#include "Runner.h"
#include "Board.h"
#include "Position.h"

class MinMaxRunner : public Runner<std::pair<Position, Position>, const Board&> {
    private:
        void run(const Board& state);

        int depth = 1;
};
