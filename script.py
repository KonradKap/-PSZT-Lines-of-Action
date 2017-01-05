#!/usr/bin/python3
from time import time
import sys
import os
sys.path.append(os.getcwd() + "/bin/lib")
from LoA import *

class bcolors:
    WHITE = '\x1b[0;37;40m'
    BLACK = '\x1b[0;34;40m' #actually blue
    EMPTY = '\x1b[0;30;40m'

def print_board(board):
    print("\x1b[2J\x1b[H")
    for y in range(8):
        for x in range(8):
            switch = {
                Field.Empty : bcolors.EMPTY + " . ",
                Field.White : bcolors.WHITE + " O ",
                Field.Black : bcolors.BLACK + " O ",
            }
            print(switch[board.get(x, y)], end="")
            #less fancy version below:
            #print(board.get(x,y), end=" ")
        print()

board = Board()
print_board(Board())

while not board.isGameOver():
    board = AI_turn(board)
    print_board(board)
    print()

print("\x1b[2J\x1b[H")
print("Winner is: " + board.getWinner())
