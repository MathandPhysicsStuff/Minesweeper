#include "functions.h"

void enqueue(coord *queue, int length, int *count, coord values)
{
	queue[*count] = values;
	*count += 1;
}

coord dequeue(coord *queue, int length, int *count)
{
	coord temp = queue[0];

	for (int i = 0; i < *count; i++)
	{
		queue[i] = queue[i+1];
	}
	*count -= 1;
	return temp;
}

void floodfill(int board[18][32], int tiles[18][32], int length, int i, int j, int new_tile)
{
	int old_tile = tiles[i][j];

	if (old_tile == new_tile) 
	{
		return;
	}

	coord queue[length];
	int count = 0;

	coord cell = { i, j };
	enqueue(queue, length, &count, cell);

	while (count > 0)
	{
		cell = dequeue(queue, length, &count);
		i = cell.x, j = cell.y;

		if (i < 1 || j < 1 || i >= 17 || j >= 31 || tiles[i][j] != old_tile || board[i][j] == 11)
		{
			continue;
		}

		else if (board[i][j] > 0 && board[i][j] < 9)
		{
			tiles[i][j] = new_tile;
			continue;	
		}

		else
		{
			tiles[i][j] = new_tile;

			cell.x = i+1, cell.y = j;
			enqueue(queue, length, &count, cell);

			cell.x = i-1, cell.y = j;
			enqueue(queue, length, &count, cell);

			cell.x = i, cell.y = j+1;
			enqueue(queue, length, &count, cell);

			cell.x = i, cell.y = j-1;
			enqueue(queue, length, &count, cell);

			cell.x = i-1, cell.y = j-1;
			enqueue(queue, length, &count, cell);

			cell.x = i-1, cell.y = j+1;
			enqueue(queue, length, &count, cell);

			cell.x = i+1, cell.y = j-1;
			enqueue(queue, length, &count, cell);

			cell.x = i+1, cell.y = j+1;
			enqueue(queue, length, &count, cell);


		}
	}
}

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

void board_logic(SDL_Event event, SDL_Rect cell_rect, SDL_Point mouse, GameState *game_state,
				 int board[18][32], int tiles[18][32], int row, int colum)
{
	int i, j;
	int new_tile = 0;
	int length = 480;
	
	cell_rect.x = 0;
	cell_rect.y = 92;
	cell_rect.w = 24;
	cell_rect.h = 24;

	for (i = 1; i <= row; i++)
	{
		
		cell_rect.x = 4;
		for (j = 1; j <= colum; j++)
		{
			if(event.button.button == SDL_BUTTON_LEFT && tiles[i][j] != 2 && game_state->gameover == SDL_FALSE)
			{
				if (SDL_PointInRect(&mouse, &cell_rect))
				{
					if (board[i][j] == 11) 
					{ 
						tiles[i][j] = 0;
						board[i][j] = 12;
						game_state->gameover = SDL_TRUE;

						for (int i = 1; i <= 16; i++)
						{
							for (int j = 1; j <= 30; j++)
							{
								if (board[i][j] == 11 && tiles[i][j] != 2)
								{
									tiles[i][j] = 0;
								}
							}
						}
					}

					if (0 < board[i][j]  && board[i][j] < 8)
					{
						tiles[i][j] = 0;
					}

					if (board[i][j] == 0)
					{
						floodfill(board, tiles, length, i, j, new_tile);
					}
				}
			}
			
			if(event.button.button == SDL_BUTTON_RIGHT && tiles[i][j] != 0 && game_state->gameover == SDL_FALSE)
			{
				if (SDL_PointInRect(&mouse, &cell_rect))
				{
					if (tiles[i][j] == 1)
					{
						tiles[i][j] = 2;
					}
					else if (tiles[i][j] == 2)
					{
						tiles[i][j] = 1;
					}
				}
			}

			cell_rect.x += 24;
		}
		cell_rect.y += 24;
	}
}


void render_board(SDL_Renderer* renderer, SDL_Texture* texture,
				  SDL_Rect image_rect, SDL_Rect cell_rect, SDL_Rect tile_rect,
				  int board[18][32], int tiles[18][32], int row, int colum)
{
	int i, j;
	int board_state = 0;
	int tile_state = 0;

	image_rect.x = 24;
	image_rect.y = 0;
	image_rect.w = 24;
	image_rect.h = 24;

	cell_rect.y = 92;
	cell_rect.w = 24;
	cell_rect.h = 24;

	tile_rect.x = 216;
	tile_rect.w = 24;
	tile_rect.h = 24;

	for (i = 1; i <= row; i++)
	{

		cell_rect.x = 4;
		for (j = 1; j <= colum; j++)
		{
			board_state = board[i][j];
			switch (board_state)
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
				case 12:
					image_rect.x = 288;
					SDL_RenderCopy(renderer, texture, &image_rect, &cell_rect);
					break;	
			}

			tile_state = tiles[i][j];
			switch (tile_state)
			{
				case 0:
					break;
				case 1:
					tile_rect.x = 216;
					SDL_RenderCopy(renderer, texture, &tile_rect, &cell_rect);
					break;
				case 2:
					tile_rect.x = 240;
					SDL_RenderCopy(renderer, texture, &tile_rect, &cell_rect);
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
