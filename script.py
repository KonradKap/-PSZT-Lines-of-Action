#!/usr/bin/python3

import sys
import os
sys.path.append(os.getcwd() + "/bin/lib")
import LoA

board = LoA.Board()

print("Czy [2, 3] jest zajete przez jakis pionek?")
print(board.isOccupied(2, 3))

print("Czy [1, 0] jest zajete przez jakis pionek?")
print(board.isOccupied(1, 0))

print("Przesun pionek z [1, 0] na [2, 3]")
board.movePawn(1, 0, 2, 3)

print("Czy [2, 3] jest zajete przez jakis pionek?")
print(board.isOccupied(2, 3))
