#pragma once

#include <vector>

#include "Runner.h"
#include "Board.h"

class MinMaxRunner : public Runner<std::vector<int>, const Board&> {
    private:
        void run(const Board& state);

        long long i;
};
