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
    def("enemyOf", &enemyOf);

    enum_<GameOverResult>("GameOverResult")
        .value("NoWinner", GameOverResult::NoWinner)
        .value("WhiteWon", GameOverResult::WhiteWon)
        .value("BlackWon", GameOverResult::BlackWon)
        .value("Draw", GameOverResult::Draw)
    ;

    bool (Board::*isOccupied_pos)(Position) const = &Board::isOccupied;
    bool (Board::*isOccupied_field)(Position, Field) const = &Board::isOccupied;
    bool (*isValid_ii)(int, int) = &Board::isValid;
    bool (*isValid_pos)(Position) = &Board::isValid;
    Field (Board::*get_ii)(int, int) const = &Board::get;
    Field (Board::*get_pos)(Position) const = &Board::get;

    class_<Board>("Board")
        .def("getPawns", &Board::getPawns)
        .def("getPawnsCount", &Board::getPawnsCount)
        .def("getAllPossibleMoves", &Board::getAllPossibleMoves)
        .def("getNeighbourFields", &Board::getNeighbourFields)
        .def("isValid", isValid_ii)
        .def("isValid", isValid_pos)
        .def("isOccupied", isOccupied_pos)
        .def("isOccupied", isOccupied_field)
        .def("movePawn", &Board::movePawn)
        .def("getMoved", &Board::getMoved)
        .def("evaluate", &Board::evaluate)
        .def("get", get_ii)
        .def("get", get_pos)
        .def("isGameOver", &Board::isGameOver)
        .def("getWinner", &Board::getWinner)
    ;
}
