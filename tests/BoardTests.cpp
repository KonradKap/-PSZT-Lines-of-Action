#include <algorithm>

#include <boost/test/auto_unit_test.hpp>

#include "print_log_value.h"

#include "Board.h"

BOOST_AUTO_TEST_SUITE(BoardTests)
BOOST_AUTO_TEST_CASE(getPawnsCountTest1) {
    Board b;
    BOOST_CHECK_EQUAL(6, b.getPawnsCount({0,1}, Direction::Down));
}

BOOST_AUTO_TEST_CASE(getAllPossibleMovesTest1) {
    Board b = Board::board_t{{
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, White, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}}
    }};
    const std::vector<Position> expected = 
        {{0,0}, {1,0}, {2,0}, {0,1}, {2,1}, {0,2}, {1,2}, {2,2}};
    const auto received = b.getAllPossibleMoves({1,1});
    BOOST_CHECK(std::is_permutation(expected.begin(), expected.end(), received.begin()));
}

BOOST_AUTO_TEST_CASE(getAllPossibleMovesTest2) {
    Board b = Board::board_t{{
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, White, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, White, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}}
    }};
    const std::vector<Position> expected = 
        {{1,0}, {2,0}, {0,1}, {2,1}, {0,2}, {1,2}, {3,3}};
    const auto received = b.getAllPossibleMoves({1,1});
    BOOST_CHECK(std::is_permutation(expected.begin(), expected.end(), received.begin()));
}

BOOST_AUTO_TEST_CASE(getAllPossibleMovesTest3) {
    Board b = Board::board_t{{
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, White, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Black, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}}
    }};
    const std::vector<Position> expected = 
        {{1,0}, {2,0}, {0,1}, {2,1}, {0,2}, {1,2}};
    const auto received = b.getAllPossibleMoves({1,1});
    BOOST_CHECK(std::is_permutation(expected.begin(), expected.end(), received.begin()));
}

BOOST_AUTO_TEST_CASE(getAllPossibleMovesTest4) {
    Board b = Board::board_t{{
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, White, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Black, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}},
        {{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty}}
    }};
    const std::vector<Position> expected = 
        {{1,0}, {2,0}, {0,1}, {2,1}, {0,2}, {1,2}, {3,3}};
    const auto received = b.getAllPossibleMoves({1,1});
    BOOST_CHECK(std::is_permutation(expected.begin(), expected.end(), received.begin()));
}
BOOST_AUTO_TEST_SUITE_END()
