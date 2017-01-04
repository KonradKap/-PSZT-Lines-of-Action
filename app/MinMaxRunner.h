#pragma once

#include <vector>
#include <limits>
#include <memory>

#include "Runner.h"
#include "Board.h"
#include "Position.h"
#include "GameTree.h"

class MinMaxRunner : public Runner<Board, const Board&> {
    public:
        ~MinMaxRunner() {}
    private:
        void run(std::shared_ptr<GameTree>& game);
        void do_running(const Board& state);

        double alphabeta(const GameTree::Node * node, double alpha, double beta);

        Board next_state;
};

Board AI_turn(const Board& current_state);
