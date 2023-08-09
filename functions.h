#ifndef FUNCTIONS_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

void generate_bombs(int board[18][32], int row, int colum, int bomb_number, int bomb_range);

void generate_numbers(int board[18][32], int row, int colum);

void render_board(SDL_Renderer* renderer, SDL_Texture* texture,
                  SDL_Rect image_rect, SDL_Rect cell_rect,
				  int board[18][32], int row, int colum);

#endif
