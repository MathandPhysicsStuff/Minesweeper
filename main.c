#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "functions.h"

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
	image = IMG_Load("spriteSheet8.png");
	if (!image) { printf("Image not loaded.\n"); }

	SDL_Texture* texturePGN = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Rect image_rect = { 72, 0, 24, 24 };
	SDL_Rect cell_rect = { 320, 320, 24, 24 };

	generate_bombs(board, 16, 30, 99, 480);
	generate_numbers(board, 16, 30);

	SDL_bool running = SDL_TRUE;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = SDL_FALSE;
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);

		render_board(renderer, texturePGN, image_rect, cell_rect, board, 16, 30);
		//SDL_RenderCopy(renderer, texturePGN, &image_rect, &cell_rect);

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















