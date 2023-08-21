#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "functions.h"

#define ROWS 18
#define COLUMS 32 

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 728;
const int SCREEN_HEIGHT = 480;

typedef enum CellStates 
{
	EMPTY = 0,
	ONE = 1, 
	TWO = 2,
	THREE = 3, 
	FOUR = 4,
	FIVE = 5, 
	SIX = 6, 
	SEVEN = 7, 
	EIGHT = 8,
	TILE = 9,
	FLAG = 10,
	BOMB = 11,
	CLICKED_BOMB = 12
} CellStates;

int board[18][32];
int tiles[18][32];
int test[18][32];


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL2 video failed to initialize: \n", SDL_GetError());
	else printf("System is ready to go!\n");


	window = SDL_CreateWindow("Hello SDL",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT,
       						  SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window,
								  -1,
								  SDL_RENDERER_ACCELERATED);

	int flags = IMG_INIT_PNG;
	int init_status = IMG_Init(flags);
	if ((init_status & flags) != flags) { printf("image init error\n"); }

	SDL_Surface* image;
	image = IMG_Load("tile_set.png");
	if (!image) { printf("Image not loaded.\n"); }

	SDL_Texture* texturePGN = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Rect image_rect = { 0, 0, 24, 24 };
	SDL_Rect cell_rect = { 0, 0, 24, 24 };
	SDL_Rect tile_rect = { 0, 0, 24, 24 };


	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 30; j++)
		{
			tiles[i][j] = 1;
		}
	}

	GameState game_state = {
							.reset = SDL_TRUE,
							.gameover = SDL_FALSE
						   };	

	//generate_bombs(board, 16, 30, 99, 480);
	//generate_numbers(board, 16, 30);

	SDL_bool running = SDL_TRUE;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			SDL_Point mouse = { event.button.x, event.button.y };

			if (event.type == SDL_QUIT)
			{
				running = SDL_FALSE;
				break;
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				board_logic(event, cell_rect, mouse, &game_state, board, tiles, 16, 30);
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_r:
						game_state.reset = SDL_TRUE;

						for (int i = 1; i <= 16; i++)
						{
							for (int j = 1; j <= 30; j++)
							{
								tiles[i][j] = 1;
							}
						}
						break;
				}
			}
		}

		if (game_state.reset == SDL_TRUE)
		{
			generate_bombs(board, 16, 30, 99, 480);
			generate_numbers(board, 16, 30);

			game_state.reset = SDL_FALSE;
			game_state.gameover = SDL_FALSE;
		}

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);

		render_board(renderer, texturePGN, image_rect, tile_rect, cell_rect, board, tiles, 16, 30);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}
	
	//freeing stuff	
	SDL_DestroyWindow(window);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texturePGN);
	IMG_Quit();
	SDL_Quit();	
	return 0;
}















