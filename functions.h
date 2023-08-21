#ifndef FUNCTIONS_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct coord
{
	int x, y;
} coord;

typedef struct GameState
{

	SDL_bool reset;
	SDL_bool gameover;

} GameState;

void generate_bombs(int board[18][32], int row, int colum, int bomb_number, int bomb_range);

void generate_numbers(int board[18][32], int row, int colum);

void board_logic(SDL_Event event, SDL_Rect cell_rect, SDL_Point mouse, GameState *game_state,
                 int board[18][32], int tiles[18][32], int row, int colum);

void render_board(SDL_Renderer* renderer, SDL_Texture* texture,
                  SDL_Rect image_rect, SDL_Rect cell_rect, SDL_Rect tile_rect,
				  int board[18][32], int tiles[18][32], int row, int colum);

#endif
