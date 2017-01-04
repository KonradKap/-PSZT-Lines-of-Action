#pragma once

#include <vector>

#include "Board.h"

class GameTree {
    public:
        struct Node {
            Node(Node* parent, const Board& state, std::vector<Node> next);
            Node(Node* parent, const Board& state);
            Node(const Board& board);
            Node();
            bool isTerminal() const;

            Node* parent;
            Board state;
            int value;
            std::vector<Node *> next;
        };

        GameTree(const Board& state, int depth);
        ~GameTree();
        void update(); //add one level to the tree
        Node * getRoot();

    private:
        void deleteNode(Node * node);
        void updateRecursively(Node * current);
        void createTree(Node * state, int depth);
        Node* root;
};
