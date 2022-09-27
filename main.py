import time
import pygame
import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer
from win32api import GetSystemMetrics

#################################################
COLOR_BG = (10, 10, 10)  # Color for background
COLOR_GRID = (40, 40, 40)  # Color for grid
COLOR_DIE_NEXT = (170, 0, 0)  # Color for next dying square
COLOR_ALIVE_NEXT = (0, 255, 0)  # Color for alive squares
COLOR_ALIVE = (255, 255, 255)

cellCount = 80
nRow = cellCount
nCol = cellCount
drawingFPS = 999
# screenWidth = GetSystemMetrics(0)
screenHeight = GetSystemMetrics(1)
#################################################
# Defining DLL and function(s)
objDLL = ctypes.CDLL("./c_sum.so")
c_updateCells = objDLL.c_updateCells
c_updateCells.argtypes = [
    ctypes.c_int64,
    ctypes.c_int64,
    ndpointer(dtype=np.int64, ndim=2, shape=(nRow, nCol)),
]
c_updateCells_restype = None
# FPS counter


def updateFps(screen, fpsClock, font, runningFPS):
    fps = str(int(fpsClock.get_fps()))
    fpsText = font.render(fps, 1, pygame.Color("coral"))
    screen.blit(fpsText, (10, 0))
    gameSpeed = f"Game speed set to {runningFPS}"
    gameSpeed = font.render(gameSpeed, 1, pygame.Color("coral"))
    screen.blit(gameSpeed, (40, 0))


def update(screen, cellsNow, size, withProgress=False):
    nRow, nCol = cellsNow.shape
    c_updateCells(nRow, nCol, cellsNow)
    cellsNow = paintCells(screen, cellsNow, size)
    return cellsNow


def paintCells(screen, cellsNow, size, withProgress=False):
    for row, col in np.ndindex(cellsNow.shape):
        color = COLOR_BG if cellsNow[row, col] == 0 else COLOR_ALIVE_NEXT
        if withProgress:
            if cellsNow[row, col] == 1:
                color = COLOR_ALIVE
            elif cellsNow[row, col] == 0:
                color = COLOR_BG
        pygame.draw.rect(screen, color, (col * size, row * size, size - 1, size - 1))
    return cellsNow


def main():
    pygame.display.set_caption("Game Of Life")
    pygame.init()
    screen = pygame.display.set_mode((screenHeight, screenHeight - 100))  # Window size
    size = screenHeight / cellCount
    size = int(size + 1)
    # Defining fpsClock to lower down the game speed
    fpsClock = pygame.time.Clock()
    # Defining font for displaying FPS
    font = pygame.font.SysFont("Arial", 18)
    # Filling window with cells. Background is actually COLOR_GRID so when we fill it with black there will be grids.
    runningFPS = 15
    cells = np.zeros((nRow, nCol), dtype=np.int64)
    screen.fill(COLOR_GRID)
    update(screen, cells, size)
    updateFps(screen, fpsClock, font, runningFPS)

    pygame.display.flip()
    pygame.display.update()
    running = False

    # Main game loop
    while True:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_1:
                    runningFPS = 5
                if event.key == pygame.K_2:
                    runningFPS = 10
                if event.key == pygame.K_3:
                    runningFPS = 15
                if event.key == pygame.K_4:
                    runningFPS = 30
                if event.key == pygame.K_5:
                    runningFPS = 999
                if event.key == pygame.K_SPACE:
                    running = not running
                    update(screen, cells, size)
                    updateFps(screen, fpsClock, font, runningFPS)
                    pygame.display.update()

            if pygame.mouse.get_pressed()[0]:
                fpsClock.tick(drawingFPS)
                pos = pygame.mouse.get_pos()
                # Finding mouse position
                cells[pos[1] // size, pos[0] // size] = 1
                paintCells(screen, cells, size)
                updateFps(screen, fpsClock, font, runningFPS)
                pygame.display.update()

            if pygame.mouse.get_pressed()[2]:
                fpsClock.tick(drawingFPS)
                pos = pygame.mouse.get_pos()
                # Finding mouse position
                cells[pos[1] // size, pos[0] // size] = 0
                paintCells(screen, cells, size)
                updateFps(screen, fpsClock, font, runningFPS)
                pygame.display.update()

        screen.fill(COLOR_GRID)
        if running:
            fpsClock.tick(runningFPS)
            cells = update(screen, cells, size, withProgress=True)
            updateFps(screen, fpsClock, font, runningFPS)
            pygame.display.update()


if __name__ == "__main__":
    main()
