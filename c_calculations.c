// cc -fPIC -shared -o c_calculations.so c_calculations.c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void c_updateCells(int64_t ROW, int64_t COL, int64_t cellsNow[][COL])
{
    size_t c_row, c_col;
    size_t i, j;
    int liveNeighbors;
    int64_t cellsUpdated[ROW][COL];
    int start_row, start_col, finish_row, finish_col;
    for (c_row = 0; c_row < ROW; c_row++)
    {
        for (c_col = 0; c_col < COL; c_col++)
        {
            liveNeighbors = 0;

            if (c_row > 0 && c_row < ROW - 1)
            {
                start_row = c_row - 1;
                finish_row = c_row + 1;
            }
            else if (c_row == 0)
            {
                start_row = c_row;
                finish_row = c_row + 1;
            }
            else
            {
                start_col = c_row - 1;
                finish_col = c_row;
            }

            if (c_col > 0 && c_col < COL - 1)
            {
                start_col = c_col - 1;
                finish_col = c_col + 1;
            }
            else if (c_col == 0)
            {
                start_col = c_col;
                finish_col = c_col + 1;
            }
            else
            {
                start_col = c_col - 1;
                finish_col = c_col;
            }
            for (i = start_row; i <= finish_row; i++)
            {
                for (j = start_col; j <= finish_col; j++)
                {
                    if ((i == c_row && j == c_col)) //  || (i < 0 || j < 0) || (i >= ROW || j >= COL)
                    {
                        continue;
                    }
                    if (cellsNow[i][j] == 1)
                    {
                        liveNeighbors++;
                    }
                }
            }
            // Live and dead cell define
            if (cellsNow[c_row][c_col] == 1 && (liveNeighbors == 2 || liveNeighbors == 3))
            {

                cellsUpdated[c_row][c_col] = 1;
            }

            else if (cellsNow[c_row][c_col] == 0 && liveNeighbors == 3)
            {

                cellsUpdated[c_row][c_col] = 1;
            }

            else
            {
                cellsUpdated[c_row][c_col] = 0;
            }
        }
    }
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellsNow[i][j] = cellsUpdated[i][j];
        }
    }
}

void c_updateCells(int64_t ROW, int64_t COL, int64_t cellsNow[][COL])
{
    size_t c_row, c_col;
    size_t i, j;
    int liveNeighbors;
    int64_t cellsUpdated[ROW][COL];
    int start_row, start_col, finish_row, finish_col;
    for (c_row = 0; c_row < ROW; c_row++)
    {
        for (c_col = 0; c_col < COL; c_col++)
        {
            liveNeighbors = 0;

            if (c_row > 0 && c_row < ROW - 1)
            {
                start_row = c_row - 1;
                finish_row = c_row + 1;
            }
            else if (c_row == 0)
            {
                start_row = c_row;
                finish_row = c_row + 1;
            }
            else
            {
                start_col = c_row - 1;
                finish_col = c_row;
            }

            if (c_col > 0 && c_col < COL - 1)
            {
                start_col = c_col - 1;
                finish_col = c_col + 1;
            }
            else if (c_col == 0)
            {
                start_col = c_col;
                finish_col = c_col + 1;
            }
            else
            {
                start_col = c_col - 1;
                finish_col = c_col;
            }
            for (i = start_row; i <= finish_row; i++)
            {
                for (j = start_col; j <= finish_col; j++)
                {
                    if ((i == c_row && j == c_col)) //  || (i < 0 || j < 0) || (i >= ROW || j >= COL)
                    {
                        continue;
                    }
                    if (cellsNow[i][j] == 1)
                    {
                        liveNeighbors++;
                    }
                }
            }
            // Live and dead cell define
            if (cellsNow[c_row][c_col] == 1 && (liveNeighbors == 2 || liveNeighbors == 3))
            {

                cellsUpdated[c_row][c_col] = 1;
            }

            else if (cellsNow[c_row][c_col] == 0 && liveNeighbors == 3)
            {

                cellsUpdated[c_row][c_col] = 1;
            }

            else
            {
                cellsUpdated[c_row][c_col] = 0;
            }
        }
    }
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellsNow[i][j] = cellsUpdated[i][j];
        }
    }
}