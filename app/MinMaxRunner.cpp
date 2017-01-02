#include "MinMaxRunner.h"

void MinMaxRunner::run(const Board& state) {
    //std::ignore = state;
    if(tree.get() == nullptr)
    	tree = std::make_shared<GameTree>(state, 2);
    else 
    	tree.get()->update();

    double inf = std::numeric_limits<double>::infinity();
	alphabeta(tree.get()->getRoot(), -inf, inf);
	//set_value(std::make_pair(Position{depth, 3}, Position{4, 5}));
}


double MinMaxRunner::alphabeta(const GameTree::Node& node, double alpha, double beta)
{
	if(node.isTerminal())
		return node.state.evaluate(node.state.getMovingPlayer());

	double v, result;
	if(node.state.getMovingPlayer() == Field::White)
	{
		v = -std::numeric_limits<double>::infinity();
		for (auto it = node.next.begin(); it != node.next.end(); ++it)
		{
			result = alphabeta((*it).state, alpha, beta);
			alpha = std::max(alpha, v);
			if(result > v)
			{
				next_state = (*it).state;
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
		for (auto it = node.next.begin(); it != node.next.end(); ++it)
		{
			result = alphabeta((*it).state, alpha, beta);
			beta = std::min(beta, v);
			if(result < v)
			{
				next_state = (*it).state;
				v = result;
			}
			if(alpha > beta)
				break;
		}
		return v;
	}

}