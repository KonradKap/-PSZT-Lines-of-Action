#include "GameTree.h"

//GameTree::Node::Node(Node* parent, Board state, std::vector<Node> next) :
//        parent(parent),
//        state(state),
//        value(state.getValue()),
//        next(next) {
//}
//
//GameTree::Node::Node() : 
//        parent(nullptr),
//        state(),
//        value(state.getValue()),
//        next() {
//}
//
GameTree::GameTree(const Board& state, int depth)
{
	Node tmp(state);
	root = &tmp;
	createTree(tmp, depth);
}

void GameTree::createTree(Node& node, int depth)
{
	if(depth == 0)
		return;
	std::vector<Board> next_states = node.state.getPossibleStates();
	for(auto it = next_states.begin(); it != next_states.end(); ++it)
	{
		Node tmp(&node, *it);
		node.next.push_back(tmp);
		createTree(tmp, depth-1);
	}
}

//add new tree level
void GameTree::update() 
{
	updateRecursively(*root);
}

void GameTree::updateRecursively(Node &current)
{
	for(auto it = current.next.begin(); it != current.next.end(); ++it)
	{
		if((*it).isTerminal())
			createTree(*it, 1); 
		else 
			updateRecursively(*it);
	}
}

GameTree::Node& GameTree::getRoot()
{
	return *root;
} 



GameTree::Node::Node(Node* parent, Board state) : parent(parent), state(state){}

GameTree::Node::Node(const Board& state) : GameTree::Node::Node(nullptr, state) {};
 
bool GameTree::Node::isTerminal() const
{
	return next.empty(); 
}