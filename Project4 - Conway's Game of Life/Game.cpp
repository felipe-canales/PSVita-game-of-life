//#include "cmath"
#include "Game.h"
//#include "InputDebug.h"
#include "GameMatrix.h"
#include "Renderer.h"

/*SDL_Texture* icon;
InputDebug* debugger;*/
GameMatrix* game_matrix;

Game::Game()
{
	is_running = false;
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error to initialize" << std::endl;
		is_running = false;
		return;
	}
	std::cout << "Initialized" << std::endl;
	window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error to create window" << std::endl;
		is_running = false;
		return;
	}
	std::cout << "Window created" << std::endl;
	renderer = Renderer::GetInstance(window, -1, 0)->GetRenderer();
	if (!renderer) {
		std::cout << "Error to create renderer" << std::endl;
		is_running = false;
		return;
	}
	std::cout << "Renderer created" << std::endl;
	is_running = true;

	//debugger = new InputDebug();
	game_matrix = new GameMatrix();
	game_matrix->toggle(1, 1);
	game_matrix->toggle(2, 1);
	game_matrix->toggle(3, 1);

	//console->print("START");
	
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickOpen(0);
}

void Game::handle_events()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_a)
			{
				game_matrix->next_step();
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				game_matrix->reset();
			}
			break;
		default:
			break;
		}
		//debugger->log(&event);
	}
}

void Game::update()
{
	SDL_Delay(30);
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 34, 145, 32, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_Texture* rendered_matrix = game_matrix->render();
	SDL_Rect rect = { 100,100,400,250 };
	SDL_RenderCopy(renderer, rendered_matrix, NULL, &rect);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

bool Game::running()
{
	return Game::is_running;
}
