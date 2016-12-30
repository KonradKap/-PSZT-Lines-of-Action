#include "Board.h"

#include <utility>
#include <queue>
#include <functional>
#include <numeric>
#include <cmath>

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

std::vector<Position> Board::getNeighbourFields(Position pos) const {
    std::vector<Position> ret;
    for(const auto vec : directions) {
        const Position temp = {
            pos.x + vec.second.x,
            pos.y + vec.second.y
        };
        if(isValid(temp))
            ret.push_back(temp);
    }
    return ret;
}

bool Board::isValid(Position position) {
    return isValid(position.x, position.y);
}

bool Board::isValid(int x, int y) {
    return x >= 0 and x < 8 and y >= 0 and y < 8;
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

double Board::evaluate(Field moving_player) const {
    auto moving_player_bonus = moving_player==White?1.0:-1.0;
    moving_player_bonus *= 4;
    return getValue(White) - getValue(Black) + moving_player_bonus;
}

Field Board::get(int x, int y) const {
    return state[x][y];
}

Field Board::get(Position pos) const {
    return get(pos.x, pos.y);
}

bool Board::isGameOver() const {
    return getWinner() != GameOverResult::NoWinner;
}

GameOverResult Board::getWinner() const {
    const auto whites = areAllConnected(White);
    const auto blacks = areAllConnected(Black);
    return static_cast<GameOverResult>(whites + (blacks<<1));
}

double Board::getValue(Field colour) const {
    auto center_mass = getMassCenter(colour);

    const auto concentration_weight = -0.5;
    const auto concentration = getDistanceSumTo(colour, center_mass);

    const auto centralization_weight = -0.5;
    const auto centralization = getDistanceSumTo(colour, {3.5, 3.5});

    center_mass.first -= 3.5;
    center_mass.first *= center_mass.first;
    center_mass.second -= 3.5;
    center_mass.second *= center_mass.second;
    const auto center_mass_value = std::sqrt(center_mass.first + center_mass.second);

    return concentration*concentration_weight +
           centralization*centralization_weight +
           center_mass_value;
}

unsigned Board::countGroupFrom(Position pawn) const {
    if(not isOccupied(pawn))
    PawnNotPresentError("There is no pawn at[" + std::to_string(pawn.x) +
            ", " + std::to_string(pawn.y) + "]");

    const auto colour = get(pawn);
    unsigned group = 1;
    std::queue<Position> queue;
    queue.push(pawn);
    std::array<std::array<bool, 8>, 8> visited;
    visited[pawn.x][pawn.y] = true;

    while(not queue.empty()) {
        const auto current = queue.front();
        queue.pop();
        for(const auto neighbour : getNeighbourFields(current)) {
            if(isOccupied(neighbour, colour) and not visited[neighbour.x][neighbour.y]) {
                queue.push(neighbour);
                visited[neighbour.x][neighbour.y] = true;
                ++group;
            }
        }
    }
    return group;
}

unsigned Board::countBiggestGroup(Field colour) const {
    //TODO: One of the first things to optimize
    std::vector<unsigned> groups;
    for(const auto pawn : getPawns(colour))
        groups.push_back(countGroupFrom(pawn));

    return *std::max_element(std::begin(groups), std::end(groups));
}

bool Board::areAllConnected(Field colour) const {
    const auto pawns = getPawns(colour);
    if(pawns.empty())
        return true;

    return countGroupFrom(pawns.front()) == pawns.size();
}

std::pair<double, double> Board::getMassCenter(Field colour) const {
    const auto pawns = getPawns(colour);
    const auto sum = std::accumulate(std::begin(pawns), std::end(pawns), Position{},
            [](const Position& accumulator, const Position& current) {
                return Position{accumulator.x + current.x,
                                accumulator.y + current.y};
            });
    return {static_cast<double>(sum.x)/pawns.size(), static_cast<double>(sum.y)/pawns.size()};
}

double Board::getDistanceSumTo(Field colour, std::pair<double, double> pos) const {
    const auto pawns = getPawns(colour);
    return std::accumulate(std::begin(pawns), std::end(pawns), 0.0,
            [&pos](double accumulator, const Position& current) {
                const auto x = current.x - pos.first;
                const auto y = current.y - pos.second;
                return accumulator + std::sqrt(x*x + y*y);
            });
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
