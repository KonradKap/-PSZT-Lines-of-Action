#pragma once

#include <vector>
#include <limits>
#include <memory>

#include "Runner.h"
#include "Board.h"
#include "Position.h"
#include "GameTree.h"

class MinMaxRunner : public Runner<std::pair<Position, Position>, const Board&> {
    private:
        void run(const Board& state);

        double alphabeta(const GameTree::Node& node, double alpha, double beta);

        int depth = 1;

        Board next_state;
        std::shared_ptr<GameTree> tree;

};
