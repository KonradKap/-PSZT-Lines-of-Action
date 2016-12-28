#pragma once

#include <map>

enum class Direction {
    Up,
    UpLeft,
    Left,
    DownLeft,
    Down,
    DownRight,
    Right,
    UpRight   
};

const std::map<Direction, std::vector<int>> directions = {
    {Direction::Up        , { 0,  1}},
    {Direction::UpLeft    , { 1,  1}},
    {Direction::Left      , { 1,  0}},
    {Direction::DownLeft  , { 1, -1}},
    {Direction::Down      , { 0, -1}},
    {Direction::DownRight , {-1, -1}},
    {Direction::Right     , {-1,  0}},
    {Direction::UpRight   , {-1,  1}},
};
