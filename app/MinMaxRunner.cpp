#include "MinMaxRunner.h"
#include <assert.h>
using namespace std::literals; //fancy millieconds

Board AI_turn(const Board& current_state) {
	MinMaxRunner runner;
	const auto thinking_time = 400ms;
	return runner.run_for(thinking_time, current_state);
}

#include <iostream>
void MinMaxRunner::treeInfo() 
{
	std::cout << "DEPTH: " << depth << "\tVISITED_NODES: " << visited_nodes << "\tLEAVES: " << leafs 
	<< "\tWIN_STATES: " << win_states << "\tAV_CHILDS_PER_NODE: " << visited_nodes/(visited_nodes-leafs) 
	<< "\tA-B_CUTOFFS: " << cutoffs << std::endl << std::endl;
	visited_nodes = cutoffs = leafs = 0;
}

void MinMaxRunner::run(const Board& state) {
    double inf = std::numeric_limits<double>::infinity();
	Board next_state = alphabeta(state, -inf, inf, depth).second;
	treeInfo();
	depth++;
	set_value(next_state);
}

std::pair<double, Board> MinMaxRunner::alphabeta(const Board& board, double alpha, double beta, int cur_depth)
{
	Board next_state;
	visited_nodes++;
	bool over = board.isGameOver();
	if(cur_depth <= 0 || over)
	{
		if(over)
			win_states++;
		leafs++;
		return std::make_pair(board.evaluate(), next_state);
	}
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
			{
				cutoffs++;
				break;
			}
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
			{
				cutoffs++;
				break;
			}
		}
		return std::make_pair(v, next_state);
	}

}
