#include "Board.h"

#include <utility> 

#include <boost/range/irange.hpp>

#include "Direction.h"
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

std::vector<std::vector<int>> Board::getPawns(Field group) const {
    std::vector<std::vector<int>> out;
    for(const auto i : boost::irange(0, 8))
        for(const auto j : boost::irange(0, 8))
            if(state[i][j] == group) 
                out.push_back({i, j});
    return out;
}

bool Board::isOccupied(int x, int y) const {
    return isOccupied(x, y, White) or isOccupied(x, y, Black);
}

bool Board::isOccupied(int x, int y, Field f) const {
    return state[x][y] == f;
}

void Board::movePawn(int from_x, int from_y, int to_x, int to_y) {
    if(not isOccupied(from_x, from_y))
        throw PawnNotPresentError("There is no pawn at[" + std::to_string(from_x) +
                ", " + std::to_string(from_y) + "]");

    state[to_x][to_y] = Empty;
    std::swap(state[from_x][from_y], state[to_x][to_y]);
}
