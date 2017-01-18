#pragma once

#include <vector>
#include <limits>

#include "Runner.h"
#include "Board.h"
#include "Position.h"

class MinMaxRunner : public Runner<Board, const Board&> {
    private:
        void run(const Board& state);

        std::pair<double, Board> alphabeta(const Board& board, double alpha, double beta, int depth);

        //Board next_state;
        int depth = 3;

        // DEBUGGING
        int cutoffs = 0;
        int visited_nodes = 0;
        int leafs = 0;
        int win_states = 0;
        void treeInfo();
};

Board AI_turn(const Board& current_state);
