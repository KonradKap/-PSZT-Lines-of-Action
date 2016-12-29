#pragma once

#include <iostream>

struct Position {
    int x;
    int y;

    Position() :
        x(), y() {}
    Position(int x, int y) : 
        x(x), y(y) {}
    Position(const Position& p) :
        x(p.x), y(p.y) {}
    Position& operator=(const Position& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    ~Position() {}

    bool operator==(const Position& p) const {
        return x==p.x and y==p.y;
    }
    bool operator!=(const Position& p) const {
        return not (*this == p);
    }
};

inline std::ostream& operator<<(std::ostream& out, const Position& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
