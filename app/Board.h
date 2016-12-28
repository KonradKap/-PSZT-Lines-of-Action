#pragma once

#include <array>
#include <vector>

class Board {
    public:
        enum Field {
            Empty,
            Black,
            White, 
        };

        typedef std::array<std::array<Field, 8>, 8> board_t;
        Board();
        Board(board_t initial_state);
        ~Board();

        std::vector<std::vector<int>> getPawns(Field group) const;

        bool isOccupied(int x, int y) const;
        bool isOccupied(int x, int y, Field f) const;

        void movePawn(int from_x, int from_y, int to_x, int to_y);
    private:
        board_t state;
};
