#pragma once

#include <map>

#include "Position.h"

enum class Direction {
    Up = 0,
    UpLeft,
    Left,
    DownLeft,
    UpRight,
    Right,
    DownRight,
    Down,
};

const std::map<Direction, Position> directions = {
    {Direction::Up        , { 0, -1}},
    {Direction::UpLeft    , {-1, -1}},
    {Direction::Left      , {-1,  0}},
    {Direction::DownLeft  , {-1,  1}},
    {Direction::UpRight   , { 1, -1}},
    {Direction::Right     , { 1,  0}},
    {Direction::DownRight , { 1,  1}},
    {Direction::Down      , { 0,  1}},
};

inline Direction opposite(Direction dir) {
    return static_cast<Direction>(7 - static_cast<int>(dir));
}
