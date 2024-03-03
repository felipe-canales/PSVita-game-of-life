#ifndef Renderer_h
#define Renderer_h
#include "SDL.h"

int const SCREEN_HEIGHT = 544;
int const SCREEN_WIDTH = 960;

class Renderer
{
public:
	static Renderer* GetInstance(SDL_Window* window, int index, int flags);
	static Renderer* GetInstance();
	SDL_Renderer* GetRenderer();
	void operator=(const Renderer&) = delete;
	Renderer(Renderer& other) = delete;
protected:
	Renderer(SDL_Window* window, int index, int flags);
	static Renderer* renderer_;
	SDL_Renderer* sdl_renderer;
};

#endif