#pragma once

#include <array>
#include <vector>

#include "Direction.h"
#include "Position.h"
#include "Field.h"

class Board {
    public:
        typedef std::array<std::array<Field, 8>, 8> board_t;
        Board();
        Board(board_t initial_state);
        ~Board();

        std::vector<Position> getPawns(Field group) const;
        int getPawnsCount(Position begin, Direction dir) const;
        std::vector<Position> getAllPossibleMoves(Position pawn) const;

        static bool isValid(Position position);
        static bool isValid(int x, int y);

        bool isOccupied(Position pos) const;
        bool isOccupied(Position pos, Field f) const;

        void movePawn(Position from, Position to);
        Board getMoved(Position from, Position to) const;

        int getValue() const;
        Field get(int x, int y) const;
        Field get(Position pos) const;
    private:
        bool enemyBlocks(Position pawn, int range, Direction dir) const;
        void putIfNotBlocked(std::vector<Position>& ret, Position pawn, Direction axis) const;
        board_t state;
};
