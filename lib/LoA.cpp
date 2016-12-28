#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "Board.h"
#include "Direction.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(LoA) {
    enum_<Direction>("Direction")
        .value("Up", Direction::Up)
        .value("UpLeft", Direction::UpLeft)
        .value("Left", Direction::Left)
        .value("DownLeft", Direction::DownLeft)
        .value("Down", Direction::Down)
        .value("DownRight", Direction::DownRight)
        .value("Right", Direction::Right)
        .value("UpRight", Direction::UpRight)
    ;

    class_<std::vector<int>>("Vector")
        .def(vector_indexing_suite<std::vector<int>>());
    class_<std::map<Direction, std::vector<int>>>("DirectionValues")
        .def(map_indexing_suite<std::map<Direction, std::vector<int>>>());
    scope().attr("directions") = directions;

    enum_<Board::Field>("Field")
        .value("White", Board::Field::White)
        .value("Black", Board::Field::Black)
        .value("Empty", Board::Field::Empty)
    ;

    bool (Board::*isOccupied_pos)(int, int) const = &Board::isOccupied;
    bool (Board::*isOccupied_field)(int, int, Board::Field) const = &Board::isOccupied;

    class_<Board>("Board")
        .def("isOccupied", isOccupied_pos)
        .def("isOccupied", isOccupied_field)
        .def("movePawn", &Board::movePawn)
    ;
}
