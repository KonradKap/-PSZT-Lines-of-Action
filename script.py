#!/usr/bin/python3
from time import time
import sys
import os
import pygame
import tkinter
from tkinter import *
from tkinter import messagebox

sys.path.append(os.getcwd() + "/bin/lib")
import LoA
import modules.colors as colors

class Game:
    FIELD_SIZE = 80
    PLAYER = LoA.Field.Empty
    (WIDTH, HEIGHT) = (640, 640)
    screen = pygame.display.set_mode((WIDTH, HEIGHT))

    running = True
    pawn_pos = LoA.Position(-1, -1)
    board = LoA.Board()

def end_game():
    if Game.board.getWinner() == Game.PLAYER:
        statement = "YOU WON!"
    else:
        statement = "You lost :<"
    if show_popup("Game over", statement + "\nDo you want to play again?"):
        main()
    else:
        Game.running = False

def drawBoard():
    for y in range(8):
        for x in range(8):
            if(x+y)%2 == 0:
                color = colors.FIELD_BRIGHT
            else:
                color = colors.FIELD_DARK
            pygame.draw.rect(Game.screen, color, (x*Game.FIELD_SIZE, y*Game.FIELD_SIZE, Game.FIELD_SIZE, Game.FIELD_SIZE))
            if Game.board.get(x,y) == LoA.Field.Black:
                pygame.draw.circle(Game.screen, colors.PAWN_BLACK, (int(x*Game.FIELD_SIZE+Game.FIELD_SIZE/2), int(y*Game.FIELD_SIZE+Game.FIELD_SIZE/2)), int(Game.FIELD_SIZE/2-2))
            elif Game.board.get(x,y) == LoA.Field.White:
                pygame.draw.circle(Game.screen, colors.PAWN_WHITE, (int(x*Game.FIELD_SIZE+Game.FIELD_SIZE/2), int(y*Game.FIELD_SIZE+Game.FIELD_SIZE/2)), int(Game.FIELD_SIZE/2-2))
    pygame.display.update()

def highlightField(x, y, color):
    pygame.draw.rect(Game.screen, color, (x, y, Game.FIELD_SIZE, Game.FIELD_SIZE), 4)
    pygame.display.update()

def highlight():
    highlightField(Game.pawn_pos.x*Game.FIELD_SIZE, Game.pawn_pos.y*Game.FIELD_SIZE, colors.PAWN_HIGHLIGHT)
    for position in Game.board.getAllPossibleMoves(Game.pawn_pos):
        highlightField(position.x*Game.FIELD_SIZE, position.y*Game.FIELD_SIZE, colors.FIELD_HIGHLIGHT)

def resetCurrentPawn():
    Game.pawn_pos = LoA.Position(-1, -1)

def getPressedField(event):
    return LoA.Position(int(event.pos[0]/Game.FIELD_SIZE), int(event.pos[1]/Game.FIELD_SIZE))

def onPawnMove(target_pos):
    Game.board = Game.board.getMoved(Game.pawn_pos, target_pos)
    drawBoard()
    if Game.board.isGameOver():
        end_game()

    Game.board = LoA.AI_turn(Game.board)
    drawBoard()
    if Game.board.isGameOver():
        end_game()

    pygame.event.clear()
    resetCurrentPawn()

def loopOnce():
    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
            Game.running = False;

        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                clicked_field_color = Game.board.get(getPressedField(event))

                if clicked_field_color == Game.PLAYER: #choosing pawn
                    Game.pawn_pos = getPressedField(event)
                    drawBoard()
                    highlight()
                elif Game.pawn_pos.x != -1:             #choosing where to move the pawn
                    possible_moves = Game.board.getAllPossibleMoves(Game.pawn_pos)
                    target_pos = getPressedField(event)
                    for move in possible_moves:
                        if move.x == target_pos.x and move.y == target_pos.y:
                            onPawnMove(target_pos)
                            break

            elif event.button == 3:
                resetCurrentPawn()
                drawBoard()

def show_popup(title, question):
    root = Tk()
    root.withdraw()
    result = messagebox.askyesno(title, question)
    root.update()
    resetCurrentPawn()
    drawBoard()
    return result

def main():
    pygame.display.set_caption("Lines of Action")

    Game.board = LoA.Board()
    resetCurrentPawn()
    drawBoard()
    
    if show_popup("Choosing side", "Do you want to play as white?\nBlack starts"):
        Game.PLAYER = LoA.Field.White
    else:
        Game.PLAYER = LoA.Field.Black
    
    if Game.PLAYER == LoA.Field.White:
        Game.board = LoA.AI_turn(Game.board)
        drawBoard()
    
    while Game.running:
        loopOnce()

pygame.init()
main()
