#pragma once
#include <cstdint>
#include <vector>
#include <cstdlib>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 5; // Tamaño de cada celda en píxeles
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

class GameOfLife
{
public:
    GameOfLife() : gameGrid(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false)), isRunning(true) {}


    void updateGrid()
    {
        std::vector<std::vector<bool>> newGrid(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));

        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            for (int y = 0; y < GRID_HEIGHT; ++y)
            {
                int neighbors = countNeighbors(x, y);
                if (gameGrid[x][y]) // Célula viva
                {
                    newGrid[x][y] = neighbors == 2 || neighbors == 3;
                }
                else // Célula muerta
                {
                    newGrid[x][y] = neighbors == 3;
                }
            }
        }

        gameGrid = newGrid;
    }

    int countNeighbors(int x, int y)
    {
        int count = 0;
        
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int neighborX = x + dx;
                int neighborY = y + dy;

                // Si las coordenadas están dentro de los límites y la celda está viva, se cuenta como vecina.
                if (neighborX >= 0 && neighborX < GRID_WIDTH && neighborY >= 0 && neighborY < GRID_HEIGHT && gameGrid[neighborX][neighborY])
                    ++count;
            }
        }

        return count;
    }

    void toggleRunning()
    {
        isRunning = !isRunning;
    }

    bool isGameRunning() const { return isRunning; }

    bool isCellAlive(int x, int y) const { return gameGrid[x][y]; }

private:
    std::vector<std::vector<bool>> gameGrid;
    bool isRunning;
};