#ifndef FUNCTIONS_H
#define FUNCTION_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

void render_board(SDL_Renderer* renderer, SDL_Texture* texture,
                  SDL_Rect image_rect, SDL_Rect cell_rect,
				  int board[18][32], int row, int colum);

#endif
