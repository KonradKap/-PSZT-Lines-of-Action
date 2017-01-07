#!/usr/bin/python3
from time import time
import sys
import os
import pygame

sys.path.append(os.getcwd() + "/bin/lib")
import LoA
import modules.colors as colors

def drawBoard(screen, board):
    for y in range(8):
        for x in range(8):
            if(x+y)%2 == 0:
                color = colors.FIELD_BRIGHT
            else:
                color = colors.FIELD_DARK
            pygame.draw.rect(screen, color, (x*80, y*80, 80, 80))
            if board.get(x,y) == LoA.Field.Black:
                pygame.draw.circle(screen, colors.PAWN_BLACK, (x*80+40, y*80+40), 40)
            elif board.get(x,y) == LoA.Field.White:
                pygame.draw.circle(screen, colors.PAWN_WHITE, (x*80+40, y*80+40), 40)

pygame.init()

(width, height) = (640, 640)
screen = pygame.display.set_mode((width, height))
screen.fill(colors.BACKGROUND)
pygame.display.flip()

board = LoA.Board()

drawBoard(screen, board)

running = True
while running:
    for event in pygame.event.get():
        if(event.type == pygame.QUIT):
            running = False
    screen.fill(colors.BACKGROUND)
    drawBoard(screen, board)
    board = LoA.AI_turn(board)
    pygame.display.update()
