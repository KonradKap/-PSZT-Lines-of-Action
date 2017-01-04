#pragma once

#include <vector>
#include <limits>

#include "Runner.h"
#include "Board.h"
#include "Position.h"

class MinMaxRunner : public Runner<Board, const Board&> {
    private:
        void run(const Board& state);

        double alphabeta(const Board& board, double alpha, double beta, int depth);

        Board next_state;
        int depth = 3;
};

inline Board AI_turn(const Board& current_state) {
	MinMaxRunner runner;
	const auto thinking_time = std::chrono::milliseconds(500);
	return runner.run_for(thinking_time, current_state);
}
