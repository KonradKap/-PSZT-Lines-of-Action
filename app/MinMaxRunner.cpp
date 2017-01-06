#include "MinMaxRunner.h"
#include <assert.h>
using namespace std::literals; //fancy millieconds

Board AI_turn(const Board& current_state) {
	MinMaxRunner runner;
	const auto thinking_time = 400ms;
	return runner.run_for(thinking_time, current_state);
}


void MinMaxRunner::run(const Board& state) {
    double inf = std::numeric_limits<double>::infinity();
	Board next_state = alphabeta(state, -inf, inf, depth).second;
	depth++;
	set_value(next_state);
}

std::pair<double, Board> MinMaxRunner::alphabeta(const Board& board, double alpha, double beta, int cur_depth)
{
	Board next_state;
	if(cur_depth <= 0 || board.isGameOver())
		return std::make_pair(board.evaluate(), next_state);
	double v, result;
	if(board.getMovingPlayer() == Field::White)
	{
		v = -std::numeric_limits<double>::infinity();
		std::vector<Board> possibleStates = board.getPossibleStates();
		for (auto next : possibleStates)
		{
			result = alphabeta(next, alpha, beta, cur_depth-1).first;
			alpha = std::max(alpha, v);
			if(result > v)
			{
				v = result;
				if(depth == cur_depth)
					next_state = next;
			}
			if(alpha >= beta)
				break;
		}
		return std::make_pair(v, next_state);
	}

	else
	{
		v = std::numeric_limits<double>::infinity();
		std::vector<Board> possibleStates = board.getPossibleStates();
		for (auto next : possibleStates)
		{
			result = alphabeta(next, alpha, beta, cur_depth-1).first;
			beta = std::min(beta, v);
			if(result < v)
			{
				next_state = next;
				v = result;
				if(depth == cur_depth)
					next_state = next;
			}
			if(alpha >= beta)
				break;
		}
		return std::make_pair(v, next_state);
	}

}
