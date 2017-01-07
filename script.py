#!/usr/bin/python3
from time import time
import sys
import os
import pygame

sys.path.append(os.getcwd() + "/bin/lib")
import LoA
import modules.colors as colors

class Game:
    FIELD_SIZE = 80
    PLAYER = LoA.Field.Black
    (WIDTH, HEIGHT) = (640, 640)

    running = True
    pawn_pos = LoA.Position(-1, -1)
    board = LoA.Board()

def drawBoard(screen):
    for y in range(8):
        for x in range(8):
            if(x+y)%2 == 0:
                color = colors.FIELD_BRIGHT
            else:
                color = colors.FIELD_DARK
            pygame.draw.rect(screen, color, (x*Game.FIELD_SIZE, y*Game.FIELD_SIZE, Game.FIELD_SIZE, Game.FIELD_SIZE))
            if Game.board.get(x,y) == LoA.Field.Black:
                pygame.draw.circle(screen, colors.PAWN_BLACK, (int(x*Game.FIELD_SIZE+Game.FIELD_SIZE/2), int(y*Game.FIELD_SIZE+Game.FIELD_SIZE/2)), int(Game.FIELD_SIZE/2))
            elif Game.board.get(x,y) == LoA.Field.White:
                pygame.draw.circle(screen, colors.PAWN_WHITE, (int(x*Game.FIELD_SIZE+Game.FIELD_SIZE/2), int(y*Game.FIELD_SIZE+Game.FIELD_SIZE/2)), int(Game.FIELD_SIZE/2))
    pygame.display.update()

def highlightField(screen, x, y, color):
    pygame.draw.rect(screen, color, (x, y, Game.FIELD_SIZE, Game.FIELD_SIZE), 4)
    pygame.display.update()

def highlight(screen):
    highlightField(screen, Game.pawn_pos.x*Game.FIELD_SIZE, Game.pawn_pos.y*Game.FIELD_SIZE, colors.PAWN_HIGHLIGHT)
    for position in Game.board.getAllPossibleMoves(Game.pawn_pos):
        highlightField(screen, position.x*Game.FIELD_SIZE, position.y*Game.FIELD_SIZE, colors.FIELD_HIGHLIGHT)

def resetCurrentPawn():
    Game.pawn_pos = LoA.Position(-1, -1)

def getPressedField(event):
    return LoA.Position(int(event.pos[0]/Game.FIELD_SIZE), int(event.pos[1]/Game.FIELD_SIZE))

def onPawnMove(target_pos):
    Game.board = Game.board.getMoved(Game.pawn_pos, target_pos)
    drawBoard(screen)

    Game.board = LoA.AI_turn(Game.board)
    drawBoard(screen)

    pygame.event.clear()
    resetCurrentPawn()

def loopOnce(screen):
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
            Game.running = False;

        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                clicked_field_color = Game.board.get(getPressedField(event))

                if clicked_field_color == Game.PLAYER: #choosing pawn
                    Game.pawn_pos = getPressedField(event)
                    drawBoard(screen)
                    highlight(screen)
                elif Game.pawn_pos.x != -1:             #choosing where to move the pawn
                    possible_moves = list(Game.board.getAllPossibleMoves(Game.pawn_pos))
                    target_pos = getPressedField(event)
                    for move in possible_moves:
                        if move.x == target_pos.x and move.y == target_pos.y:
                            onPawnMove(target_pos)
                            break

            elif event.button == 3:
                resetCurrentPawn()
                drawBoard(screen)
               
pygame.init()

screen = pygame.display.set_mode((Game.WIDTH, Game.HEIGHT))
screen.fill(colors.BACKGROUND)
pygame.display.flip()

drawBoard(screen)

while Game.running:
    loopOnce(screen)
