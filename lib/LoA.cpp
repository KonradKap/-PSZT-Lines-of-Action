#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "Board.h"
#include "Direction.h"
#include "Position.h"
#include "Field.h"

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

	class_<Position>("Position")
		.def(init<int, int>())
		.def(init<const Position&>())
		.def_readwrite("x", &Position::x)
		.def_readwrite("y", &Position::y)
	;

    class_<std::map<Direction, Position>>("DirectionValues")
        .def(map_indexing_suite<std::map<Direction, Position>>());
    scope().attr("directions") = directions;
    class_<std::vector<Position>>("Vector")
        .def(vector_indexing_suite<std::vector<Position>>());
    def("opposite", &opposite);

    enum_<Field>("Field")
        .value("White", Field::White)
        .value("Black", Field::Black)
        .value("Empty", Field::Empty)
    ;

    bool (Board::*isOccupied_pos)(Position) const = &Board::isOccupied;
    bool (Board::*isOccupied_field)(Position, Field) const = &Board::isOccupied;
    bool (*isValid_ii)(int, int) = &Board::isValid;
    bool (*isValid_pos)(Position) = &Board::isValid;
    Field (Board::*get_ii)(int, int) const = &Board::get;
    Field (Board::*get_pos)(Position) const = &Board::get;

    class_<Board>("Board")
        .def("isOccupied", isOccupied_pos)
        .def("isOccupied", isOccupied_field)
        .def("movePawn", &Board::movePawn)
        .def("getPawns", &Board::getPawns)
        .def("getPawnsCount", &Board::getPawnsCount)
        .def("getAllPossibleMoves", &Board::getAllPossibleMoves)
        .def("isValid", isValid_ii)
        .def("isValid", isValid_pos)
        .def("getMoved", &Board::getMoved)
        .def("getValue", &Board::getValue)
        .def("get", get_ii)
        .def("get", get_pos)
    ;
    def("enemyOf", &enemyOf);
}
