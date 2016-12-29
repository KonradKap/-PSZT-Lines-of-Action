#include "MinMaxRunner.h"

void MinMaxRunner::run(const Board& state) {
    std::ignore = state;

    //kolejna iteracja
    ++depth;
    //update zwroconej wartosci
    set_value(std::make_pair(Position{depth, 3}, Position{4, 5}));
}
