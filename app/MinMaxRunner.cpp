#include "MinMaxRunner.h"

void MinMaxRunner::run(const Board& state) {
    double inf = std::numeric_limits<double>::infinity();
	alphabeta(state, -inf, inf, depth);
	depth++;
	set_value(next_state);
}


double MinMaxRunner::alphabeta(const Board& board, double alpha, double beta, int depth)
{
	if(depth <= 0 || board.isGameOver())
		return board.evaluate();

	double v, result;
	if(board.getMovingPlayer() == Field::White)
	{
		v = -std::numeric_limits<double>::infinity();
		std::vector<Board> possibleStates = board.getPossibleStates();
		for (auto it = possibleStates.begin(); it != possibleStates.end(); ++it)
		{
			result = alphabeta(*it, alpha, beta, depth-1);
			alpha = std::max(alpha, v);
			if(result > v)
			{
				next_state = *it;
				v = result;
			}
			if(alpha > beta)
				break;
		}
		return v;
	}

	else
	{
		v = std::numeric_limits<double>::infinity();
		std::vector<Board> possibleStates = board.getPossibleStates();
		for (auto it = possibleStates.begin(); it != possibleStates.end(); ++it)
		{
			result = alphabeta(*it, alpha, beta, depth-1);
			beta = std::min(beta, v);
			if(result < v)
			{
				next_state = (*it);
				v = result;
			}
			if(alpha > beta)
				break;
		}
		return v;
	}

}
