#ifndef GameMatrix_h
#define GameMatrix_h
#include "Renderer.h"
#include "SDL.h"

int const HEIGHT = 5;
int const WIDTH = 8;

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
	bool matrix[HEIGHT][WIDTH];
	bool next_matrix[HEIGHT][WIDTH];
	SDL_Texture* texture;
};

#endif
