#include "functions.h"

void generate_bombs(int board[18][32], int row, int colum, int bomb_number, int bomb_range)
{
	srand(time(NULL));
	
	int i, j, b, array[bomb_range];
	int bomb_positions[bomb_number];
	SDL_bool append;	

	memset(bomb_positions, 0, bomb_number * sizeof(int));
	memset(array, 0, bomb_range * sizeof(int));

	for (i = 0; i < bomb_number; i++)
	{
		b = (rand() % bomb_range) + 1;
		
		append = SDL_TRUE;	
		for (j = 0; j < i; j++)
		{
			if (b == bomb_positions[j])
			{
				append = SDL_FALSE;
				i -= 1;
				break;
			}
		}
		if (append == SDL_TRUE)
		{
			bomb_positions[i] = b;
			array[bomb_positions[i]] = 11;
		}
	}

	int a = 0;	
	for (int x = 1; x <= row; x++)
	{
		for (int y = 1; y <= colum; y++)
		{
			board[x][y] = array[a];	
			a++;
		}
	}
}


void generate_numbers(int board[18][32], int row, int colum)
{
	int i, j, bomb_counter;

	for (i = 1; i <= row; i++)
	{	
		for (j = 1; j <= colum; j++)
		{
			bomb_counter = 0;
			if (board[i][j] == 0)
			{
				if (board[i-1][j-1] == 11) bomb_counter += 1;
				if (board[i-1][j] == 11) bomb_counter += 1;
				if (board[i-1][j+1] == 11) bomb_counter += 1;
				if (board[i][j+1] == 11) bomb_counter += 1;
				if (board[i+1][j+1] == 11) bomb_counter += 1;
				if (board[i+1][j] == 11) bomb_counter += 1;
				if (board[i+1][j-1] == 11) bomb_counter += 1;
				if (board[i][j-1] == 11) bomb_counter += 1;

				if (bomb_counter == 0) board[i][j] = 0;
				if (bomb_counter == 1) board[i][j] = 1;
				if (bomb_counter == 2) board[i][j] = 2;
				if (bomb_counter == 3) board[i][j] = 3;
				if (bomb_counter == 4) board[i][j] = 4;
				if (bomb_counter == 5) board[i][j] = 5;
				if (bomb_counter == 6) board[i][j] = 6;
				if (bomb_counter == 7) board[i][j] = 7;
				if (bomb_counter == 8) board[i][j] = 8;
			}
			else board[i][j] = 11;
		}
	}
}


void render_board(SDL_Renderer* renderer, SDL_Texture* texture,
				  SDL_Rect image_rect, SDL_Rect cell_rect,
				  int board[18][32], int row, int colum)
{
	int i, j;
	int state = 0;

	image_rect.x = 24;
	image_rect.y = 0;
	image_rect.w = 24;
	image_rect.h = 24;

	cell_rect.y = 92;
	cell_rect.w = 24;
	cell_rect.w = 24;

	for (i = 1; i <= row; i++)
	{

		cell_rect.x = 4;
		for (j = 1; j <= colum; j++)
		{
			state = board[i][j];
			switch (state)
			{
				case 0:
					image_rect.x = 0;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 1:
					image_rect.x = 24;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 2:
					image_rect.x = 48;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 3:
					image_rect.x = 72;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 4:
					image_rect.x = 96;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 5:
					image_rect.x = 120;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 6:
					image_rect.x = 144;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 7:
					image_rect.x = 168;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 8:
					image_rect.x = 192;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
				case 11:
					image_rect.x = 264;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
			}
			cell_rect.x += 24;
		}
		cell_rect.y += 24;
	}

	SDL_Rect outlineT = {0, 88, 728, 4};
	SDL_Rect outlineB = {4, 476, 728, 4}; 
	SDL_Rect outlineL = {0, 88, 4, 392};
	SDL_Rect outlineR = {724, 88, 4, 392};

	SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
	SDL_RenderFillRect(renderer, &outlineT);
	SDL_RenderFillRect(renderer, &outlineL);

	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
	SDL_RenderFillRect(renderer, &outlineB);
	SDL_RenderFillRect(renderer, &outlineR);
}
