#pragma once

#include <vector>
#include <limits>
#include <memory>

#include "Runner.h"
#include "Board.h"
#include "Position.h"
#include "GameTree.h"

class MinMaxRunner : public Runner<Board, const Board&> {
    private:
        void run(const Board& state);

        double alphabeta(const GameTree::Node& node, double alpha, double beta);

        Board next_state;
        std::shared_ptr<GameTree> tree;
};

inline Board AI_turn(const Board& current_state) {
	MinMaxRunner runner;
	const auto thinking_time = std::chrono::milliseconds(500);
	return runner.run_for(thinking_time, current_state);
}
