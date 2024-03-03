#ifndef GameMatrix_h
#define GameMatrix_h
#include "Renderer.h"
#include "SDL.h"

int const MATRIX_HEIGHT = 21;
int const MATRIX_WIDTH = 40;
int const MATRIX_TILE_SIZE = 24;

class GameMatrix {
public:
	GameMatrix();
	~GameMatrix();

	void reset();
	void toggle(int x, int y);
	void next_step();
	SDL_Texture* render();
private:
	int neighbors(int x, int y);
	bool matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
	bool next_matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
};

#endif
