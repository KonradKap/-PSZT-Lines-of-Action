#!/usr/bin/python3

import sys
import os
sys.path.append(os.getcwd() + "/bin/lib")
from LoA import *

board = Board()

print("Czy [2, 3] jest zajete przez jakis pionek?")
print(board.isOccupied(Position(2, 3)))

print("Czy [1, 0] jest zajete przez jakis pionek?")
print(board.isOccupied(Position(1, 0)))

print("Przesun pionek z [1, 0] na [2, 3]")
board.movePawn(Position(1, 0), Position(2, 3))

print("Czy [2, 3] jest zajete przez jakis pionek?")
print(board.isOccupied(Position(2, 3)))

print("Podaj wszystkie mozliwe ruchy z [2, 3]")
vec = list(board.getAllPossibleMoves(Position(2, 3)))

for position in vec:
    print(str(position.x) + " " + str(position.y))

print("Board: ")
for y in range(8):
    for x in range(8):
        print(board.get(x, y), end=" ")
    print()
    
