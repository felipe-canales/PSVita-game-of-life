#include "GameMatrix.h"

GameMatrix::GameMatrix()
{
	reset();
	SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 400, 250);
}

GameMatrix::~GameMatrix()
{
	SDL_DestroyTexture(texture);
}

void GameMatrix::reset()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			matrix[j][i] = false;
			next_matrix[j][i] = false;
		}
	}
}

void GameMatrix::toggle(int x, int y)
{
	matrix[y][x] = !matrix[y][x];
}

void GameMatrix::next_step()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			int live_neighbors = neighbors(i, j);
			if (matrix[j][i])
			{
				next_matrix[j][i] = (2 <= live_neighbors && live_neighbors <= 3);
			}
			else
			{
				next_matrix[j][i] = (live_neighbors == 3);
			}
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			matrix[j][i] = next_matrix[j][i];
		}
	}
}

SDL_Texture* GameMatrix::render()
{
	SDL_Renderer* renderer = Renderer::GetInstance()->GetRenderer();
	SDL_SetRenderTarget(renderer, texture);
	SDL_Rect rect;

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			int color = 255 * (int)matrix[j][i];
			rect = { i * 50, j * 50, 49, 49 };
			SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	SDL_SetRenderTarget(renderer, NULL);
	return texture;
}

int GameMatrix::neighbors(int x, int y)
{
	bool top_row = y == 0;
	bool bottom_row = y == HEIGHT - 1;
	bool left_col = x == 0;
	bool right_col = x == WIDTH - 1;
	int alive = 0;
	if (!top_row && !left_col && matrix[y - 1][x - 1])
		alive++;
	if (!top_row && matrix[y - 1][x])
		alive++;
	if (!top_row && !right_col && matrix[y - 1][x + 1])
		alive++;
	if (!left_col && matrix[y][x - 1])
		alive++;
	if (!right_col && matrix[y][x + 1])
		alive++;
	if (!bottom_row && !left_col && matrix[y + 1][x - 1])
		alive++;
	if (!bottom_row && matrix[y + 1][x])
		alive++;
	if (!bottom_row && !right_col && matrix[y + 1][x + 1])
		alive++;
	return alive;
}
