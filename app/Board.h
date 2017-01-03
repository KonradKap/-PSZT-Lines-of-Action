#pragma once

#include <array>
#include <vector>

#include "Direction.h"
#include "Position.h"
#include "Field.h"

enum GameOverResult {
    NoWinner,
    WhiteWon,
    BlackWon,
    Draw,
};

class Board {
    public:
        typedef std::array<std::array<Field, 8>, 8> board_t;
        Board();
        Board(board_t initial_state);
        ~Board();

        std::vector<Position> getPawns(Field group) const;
        int getPawnsCount(Position begin, Direction dir) const;
        std::vector<Position> getAllPossibleMoves(Position pawn) const;
        std::vector<Position> getNeighbourFields(Position pos) const;

        std::vector<Board> getPossibleStates() const; // new

        static bool isValid(Position position);
        static bool isValid(int x, int y);

        bool isOccupied(Position pos) const;
        bool isOccupied(Position pos, Field f) const;

        Board getMoved(Position from, Position to) const;

        double evaluate() const;

        Field get(int x, int y) const;
        Field get(Position pos) const;

        Field getMovingPlayer() const;

        bool isGameOver() const;
        GameOverResult getWinner() const;
    private:
        double getValue(Field moving_player) const;
        void makeTurn(Position from, Position to);

        unsigned countGroupFrom(Position pawn) const;
        unsigned countBiggestGroup(Field colour) const;
        bool areAllConnected(Field colour) const;

        std::pair<double, double> getMassCenter(Field colour) const;
        double getDistanceSumTo(Field colour, std::pair<double, double> pos) const;

        bool enemyBlocks(Position pawn, int range, Direction dir) const;
        void putIfNotBlocked(std::vector<Position>& ret, Position pawn, Direction axis) const;

        board_t state;
        Field current_player;
};
