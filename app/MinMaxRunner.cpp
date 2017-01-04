#include "MinMaxRunner.h"

Board AI_turn(const Board& current_state) {
	MinMaxRunner runner;
	const auto thinking_time = std::chrono::milliseconds(5000);
	return runner.run_for(thinking_time, current_state);
}

void MinMaxRunner::do_running(const Board& state) {
    auto tree = std::make_shared<GameTree>(state, 1);
    while(can_continue())
        run(tree);
}

void MinMaxRunner::run(std::shared_ptr<GameTree>& tree) {
    tree.get()->update();

    double inf = std::numeric_limits<double>::infinity();
	alphabeta(tree.get()->getRoot(), -inf, inf);
	set_value(next_state);
}


double MinMaxRunner::alphabeta(const GameTree::Node * node, double alpha, double beta)
{
	if(node->isTerminal())
		return node->state.evaluate();

	double v, result;
	if(node->state.getMovingPlayer() == Field::White)
	{
		v = -std::numeric_limits<double>::infinity();
		for (auto it = node->next.begin(); it != node->next.end(); ++it)
		{
			result = alphabeta(*it, alpha, beta);
			alpha = std::max(alpha, v);
			if(result > v)
			{
				next_state = (*it)->state;
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
		for (auto it = node->next.begin(); it != node->next.end(); ++it)
		{
			result = alphabeta(*it, alpha, beta);
			beta = std::min(beta, v);
			if(result < v)
			{
				next_state = (*it)->state;
				v = result;
			}
			if(alpha > beta)
				break;
		}
		return v;
	}

}
