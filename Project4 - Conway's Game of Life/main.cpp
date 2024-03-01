#include "Game.h"

//Screen dimension constants
enum {
	SCREEN_WIDTH = 960,
	SCREEN_HEIGHT = 544
};


Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();

	game->init("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (game->running()) {
		game->handle_events();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}