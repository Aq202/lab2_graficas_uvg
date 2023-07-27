#pragma once
#include <cstdint>
#include <vector>
#include <cstdlib>
#include <iostream>

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
        // ignorar la celula actual
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

  void createPattern(const std::vector<std::pair<int, int>> &patternCoordinates)
  {
    for (const auto &coord : patternCoordinates)
    {
      int coordX = coord.first;
      int coordY = coord.second;

       if (coordX>= 0 && coordX < GRID_WIDTH && coordY >= 0 && coordY < GRID_HEIGHT)
      gameGrid[coordX][coordY] = true;
    }
  }

  void createBlock(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {x, y}, {x + 1, y}, {x, y + 1}, {x + 1, y + 1}};
    createPattern(pattern);
  }

  void createBeacon(const int x, const int y)
  {
    createBlock(x, y);
    createBlock(x + 2, y + 2);
  }

  void createBlinker(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {x, y}, {x + 1, y}, {x + 2, y}};
    createPattern(pattern);
  }

  void createToad(const int x, const int y)
  {
    createBlinker(x, y);
    createBlinker(x + 1, y + 1);
  }

  void createGlider(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {x + 1, y}, {x + 2, y + 1}, {x, y + 2}, {x + 1, y + 2}, {x + 2, y + 2}};
    createPattern(pattern);
  }

  void createLWSS(const int x, const int y)
  {
    std::vector<std::pair<int, int>> LWSS_pattern = {
        {x + 1, y}, {x + 2, y}, {x, y + 1}, {x + 1, y + 1}, {x + 2, y + 1}, {x + 3, y + 1}, {x, y + 2}, {x + 1, y + 2}, {x + 3, y + 2}, {x + 4, y + 2}, {x + 2, y + 3}, {x + 3, y + 3}};

    createPattern(LWSS_pattern);
  }

  void createPenta(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {5, 4}, {6, 4}, {7, 3}, {7, 5}, {8, 4}, {9, 4}, {10, 4}, {11, 3}, {11, 5}, {12, 4}, {13, 4}, {14, 4}};
    createPattern(pattern);
  }
  void createBoat(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2}};
    createPattern(pattern);
  }
  void createHWSS(const int x, const int y)
  {
    std::vector<std::pair<int, int>> pattern = {
        {1, 1}, {1, 4}, {2, 5}, {3, 1}, {3, 5}, {4, 2}, {4, 3}, {4, 4}, {4, 5}};
    createPattern(pattern);
  }

  void generateRandomOrganisms(int numOrganisms, int semilla = 20) {
    srand(semilla); 

    for (int i = 0; i < numOrganisms; i++) {

        // Obtener puntos dentro de la pantalla
        int x = rand() % GRID_WIDTH + 1; 
        int y = rand() % GRID_HEIGHT + 1;

        int organism = rand() % 8 + 1; // random entre 1 y 8

        switch (organism) {
            case 1:
                createBlock(x, y);
                break;
            case 2:
                createBeacon(x, y);
                break;
            case 3:
                createBlinker(x, y);
                break;
            case 4:
                createToad(x, y);
                break;
            case 5:
                createGlider(x, y);
                break;
            case 6:
                createLWSS(x, y);
                break;
            case 7:
                createPenta(x, y);
                break;
            case 8:
                createHWSS(x, y);
                break;
            default:
                break;
        }
    }
}

private:
  std::vector<std::vector<bool>> gameGrid;
  bool isRunning;
};