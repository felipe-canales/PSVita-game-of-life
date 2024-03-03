#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void init(const char* title);
	void handle_events();
	void update();
	void render();
	void clean();

	bool running();
private:
	bool is_running;
	bool paused;
	int delay;
	int counter;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif
