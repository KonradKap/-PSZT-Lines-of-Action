#pragma once

#include <vector>

#include "Board.h"

class GameTree {
    public:
        struct Node {
            Node(Node* parent, Board state, std::vector<Node> next);
            Node(Node* parent, Board state);
            Node(const Board& board);
            Node();
            bool isTerminal() const;

            Node* parent;
            Board state;
            int value;
            std::vector<Node> next;
        };

        GameTree(const Board& state, int depth);
        void update(); //add more levels to the tree (up to depth)
        Node& getRoot();

    private:
        void updateRecursively(Node& current);
        void createTree(Node& state, int depth);
        Node* root;


};
