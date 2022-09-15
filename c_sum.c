// cc -fPIC -shared -o c_sum.so c_sum.c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
void c_updateCells(int64_t ROW, int64_t COL, int64_t cellsNow[][COL])
{
    size_t c_row, c_col;
    size_t i, j;
    int liveNeighbors;
    int64_t cellsUpdated[ROW][COL];
    for (c_row = 0; c_row < ROW; c_row++)
    {
        for (c_col = 0; c_col < COL; c_col++)
        {
            int liveNeighbors = 0;
            // TOP PART
            if (c_row == 0)
            {
                // TOP LEFT
                if (c_col == 0)
                {
                    for (i = c_row; i <= c_row + 1; i++)
                    {
                        for (j = c_col; j <= c_col + 1; j++)
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
                }
                // TOP RIGHT
                else if (c_col == COL)
                {
                    for (i = c_row; i <= c_row + 1; i++)
                    {
                        for (j = c_col - 1; j <= c_col; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {
                                liveNeighbors++;
                            }
                        }
                    }
                }
                // TOP MIDDLE
                else
                {
                    for (i = c_row; i <= c_row + 1; i++)
                    {
                        for (j = c_col - 1; j <= c_col + 1; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {
                                liveNeighbors++;
                            }
                        }
                    }
                }
            }
            // BOTTOM PART
            else if (c_row == ROW)
            {
                // BOTTOM LEFT
                if (c_col == 0)
                {
                    for (i = c_row - 1; i <= c_row; i++)
                    {
                        for (j = c_col; j <= c_col + 1; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {
                                liveNeighbors++;
                            }
                        }
                    }
                }
                // BOTTOM RIGHT
                if (c_col == COL)
                {
                    for (i = c_row - 1; i <= c_row; i++)
                    {
                        for (j = c_col - 1; j <= c_col; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {
                                liveNeighbors++;
                            }
                        }
                    }
                }
                // BOTTOM MIDDLE
                else
                {
                    for (i = c_row - 1; i <= c_row; i++)
                    {
                        for (j = c_col - 1; j <= c_col + 1; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {
                                liveNeighbors++;
                            }
                        }
                    }
                }
            }
            // LEFT PART
            else if (c_col == 0)
            {
                for (i = c_row - 1; i <= c_row + 1; i++)
                {
                    for (j = c_col; j <= c_col + 1; j++)
                    {
                        if ((i == c_row && j == c_col))
                        {
                            continue;
                        }
                        if (cellsNow[i][j] == 1)
                        {
                            liveNeighbors++;
                        }
                    }
                }
            }
            // RIGHT PART
            else if (c_col == COL)
            {
                for (i = c_row - 1; i <= c_row + 1; i++)
                {
                    for (j = c_col - 1; j <= c_col; j++)
                    {
                        if ((i == c_row && j == c_col))
                        {
                            continue;
                        }
                        if (cellsNow[i][j] == 1)
                        {
                            liveNeighbors++;
                        }
                    }
                }
            }
            // MIDDLE PART
            else
            {
                {
                    for (i = c_row - 1; i <= c_row + 1; i++)
                    {
                        for (j = c_col - 1; j <= c_col + 1; j++)
                        {
                            if ((i == c_row && j == c_col))
                            {
                                continue;
                            }
                            if (cellsNow[i][j] == 1)
                            {

                                liveNeighbors++;
                            }
                        }
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