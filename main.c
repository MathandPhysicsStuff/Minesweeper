#include <stdio.h>

#include "SDL2/SDL.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 480;

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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();	
	return 0;
}















