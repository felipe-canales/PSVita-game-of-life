#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();

	game->init("Game of Life");

	while (game->running()) {
		game->handle_events();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}