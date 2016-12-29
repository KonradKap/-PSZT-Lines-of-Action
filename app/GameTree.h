#pragma once

#include <vector>

#include "Board.h"

class GameTree {
    public:

    private:
        struct Node {
            Node(Node* parent, Board state, std::vector<Node> next);
            Node();

            Node* parent;
            Board state;
            int value;
            std::vector<Node> next;
        };
    
    Node* root;
};
