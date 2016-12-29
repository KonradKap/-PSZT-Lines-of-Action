#include "GameTree.h"

GameTree::Node::Node(Node* parent, Board state, std::vector<Node> next) :
        parent(parent),
        state(state),
        value(state.getValue()),
        next(next) {
}

GameTree::Node::Node() : 
        parent(nullptr),
        state(),
        value(state.getValue()),
        next() {
}

