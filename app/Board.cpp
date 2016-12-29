#include "Board.h"

#include <utility>
#include <functional>

#include <boost/range/irange.hpp>

#include "Exceptions.h"

Board::Board() :
        state{{
            {{Empty, White, White, White, White, White, White, Empty}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Black, Empty, Empty, Empty, Empty, Empty, Empty, Black}},
            {{Empty, White, White, White, White, White, White, Empty}}
        }} {
}

Board::Board(board_t initial_state) :
        state(initial_state) {

}

Board::~Board() {
}

std::vector<Position> Board::getPawns(Field group) const {
    std::vector<Position> out;
    for(const auto i : boost::irange(0, 8))
        for(const auto j : boost::irange(0, 8))
            if(state[i][j] == group) 
                out.push_back({i, j});
    return out;
}

bool Board::isValid(Position position) {
    return isValid(position.x, position.y);
}

bool Board::isValid(int x, int y) {
    return x >= 0 and x < 8 and y >= 0 and y < 8;
}

int Board::getPawnsCount(Position begin, Direction dir) const {
    int ret = 0;
    while(isValid(begin)) {
        if(isOccupied(begin))
            ++ret;
        begin.x += directions.at(dir).x;
        begin.y += directions.at(dir).y;
    }
    return ret;
}

void Board::putIfNotBlocked(std::vector<Position>& ret, Position pawn, Direction axis) const {
    const int range =
        getPawnsCount(pawn, axis) + getPawnsCount(pawn, opposite(axis)) - 1;
    if(not enemyBlocks(pawn, range, axis)) {
        const Position pos = {
            pawn.x + range*directions.at(axis).x,
            pawn.y + range*directions.at(axis).y
        };
        if(isValid(pos) and not isOccupied(pos, get(pawn)))
            ret.push_back(pos);
    }
    if(not enemyBlocks(pawn, range, opposite(axis))) {
        const Position pos = {
            pawn.x - range*directions.at(axis).x,
            pawn.y - range*directions.at(axis).y
        };
        if(isValid(pos) and not isOccupied(pos, get(pawn)))
            ret.push_back(pos);
    }
}

std::vector<Position> Board::getAllPossibleMoves(Position pawn) const {
    if(not isOccupied(pawn))
    PawnNotPresentError("There is no pawn at[" + std::to_string(pawn.x) +
            ", " + std::to_string(pawn.y) + "]");
    
    std::vector<Position> ret;
    ret.reserve(8);
    
    putIfNotBlocked(ret, pawn, Direction::Right);
    putIfNotBlocked(ret, pawn, Direction::Down);
    putIfNotBlocked(ret, pawn, Direction::UpLeft);
    putIfNotBlocked(ret, pawn, Direction::UpRight);
    return ret;
}

bool Board::enemyBlocks(Position pawn, int range, Direction dir) const {
    const auto pawn_side = state[pawn.x][pawn.y];
    for(const auto i : boost::irange(0, range)) {
        if(isOccupied({pawn.x + directions.at(dir).x * i,
                       pawn.y + directions.at(dir).y * i},
                       enemyOf(pawn_side)))
            return true;
    }
    return false;
}

bool Board::isOccupied(Position pos) const {
    return isOccupied(pos, White) or isOccupied(pos, Black);
}

bool Board::isOccupied(Position pos, Field f) const {
    if(not isValid(pos))
        return false;
    return state[pos.x][pos.y] == f;
}

void Board::movePawn(Position from, Position to) {
    if(not isOccupied(from))
        throw PawnNotPresentError("There is no pawn at[" + std::to_string(from.x) +
                ", " + std::to_string(from.y) + "]");

    state[to.x][to.y] = Empty;
    std::swap(state[from.x][from.y], state[to.x][to.y]);
}

Board Board::getMoved(Position from, Position to) const {
    Board ret = *this;
    ret.movePawn(from, to);
    return ret;
}

int Board::getValue() const {
    return 1;
}

Field Board::get(int x, int y) const {
    return state[x][y];
}

Field Board::get(Position pos) const {
    return get(pos.x, pos.y);
}
