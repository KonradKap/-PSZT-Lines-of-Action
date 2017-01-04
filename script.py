#!/usr/bin/python3
from time import time
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
t1 = time();
board = AI_turn(board)
t2 = time();
print("")
print_board(board)
print(t2-t1)