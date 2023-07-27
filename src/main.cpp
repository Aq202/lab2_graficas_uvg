#include <SDL.h>
#include "gameOfLife.h"
#include <ctime>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Crear el juego
    GameOfLife game;


    game.generateRandomOrganisms(500, 4);

    // Bucle principal
    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                    game.toggleRunning();
            }
        }

        if (game.isGameRunning())
        {
            game.updateGrid();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dibujar la cuadrícula
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            for (int y = 0; y < GRID_HEIGHT; ++y)
            {
                if (game.isCellAlive(x, y))
                {
                    // Dibujar una celda viva en blanco
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                else
                {
                    // Dibujar una celda muerta en negro
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }

                SDL_Rect cellRect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Retardo de actualización (milisegundos)
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}