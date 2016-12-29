#pragma once

enum Field {
    Black = 0, //bad
    White = 1, //good
    Empty = 2,
};

inline Field enemyOf(Field f) {
    if (f == Field::Empty)
        return f;
    return static_cast<Field>(not static_cast<bool>(f));
}

