#!/usr/bin/python3

import sys
import os
sys.path.append(os.getcwd() + "/bin/lib")
from LoA import *

def print_board(board):
    for y in range(8):
        for x in range(8):
            print(board.get(x, y), end=" ")
        print()

board = Board()

print_board(board)

board = AI_turn(board)
print("")
print_board(board)
