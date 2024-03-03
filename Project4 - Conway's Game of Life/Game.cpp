#include "Game.h"
#include "GameMatrix.h"
#include "Renderer.h"
#include "TextHandler.h"

#define FRONT_SCREEN 0
#define X_BUTTON 2
#define L_BUTTON 4
#define R_BUTTON 5
#define O_BUTTON 1
#define SELECT_BUTTON 10

GameMatrix* game_matrix;
TextHandler* text;

const std::string SPEED_TEXT = "Speed: ";


Game::Game()
{
	is_running = false;
	paused = true;
	delay = 9;
	counter = 0;
}

Game::~Game() {}

void Game::init(const char* title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error to initialize" << std::endl;
		is_running = false;
		return;
	}
	std::cout << "Initialized" << std::endl;
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
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

	game_matrix = new GameMatrix();
	text = new TextHandler();
	game_matrix->toggle(21, 1);
	game_matrix->toggle(22, 2);
	game_matrix->toggle(20, 3);
	game_matrix->toggle(21, 3);
	game_matrix->toggle(22, 3);

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
		case SDL_MOUSEBUTTONDOWN:
			{
				int tile_x = (int)(event.button.x / MATRIX_TILE_SIZE);
				int tile_y = (int)(event.button.y / MATRIX_TILE_SIZE);
				game_matrix->toggle(tile_x, tile_y);
			}
			break;
		case SDL_JOYBUTTONDOWN:
			if (event.jbutton.button == X_BUTTON)
			{
				paused = !paused;
				counter = 0;
			}
			if (event.jbutton.button == O_BUTTON && paused)
				game_matrix->next_step();
			if (event.jbutton.button == SELECT_BUTTON)
			{
				game_matrix->reset();
				paused = true;
				counter = 0;
			}
			if (event.jbutton.button == L_BUTTON && delay < 15)
				delay = delay + 2;
			if (event.jbutton.button == R_BUTTON && delay > 1)
				delay = delay - 2;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	SDL_Delay(10);
	counter++;
	if (!paused && counter > delay)
	{
		game_matrix->next_step();
		counter = 0;
	}
}

void Game::render()
{
	int line1 = 512, line2 = 528;
	// Get component textures
	SDL_Texture* rendered_matrix = game_matrix->render();
	SDL_Rect matrix_loc = { 0,0,MATRIX_WIDTH * MATRIX_TILE_SIZE,MATRIX_HEIGHT * MATRIX_TILE_SIZE };
	// Draw screen
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0xEC, 0xC0, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, rendered_matrix, NULL, &matrix_loc);

	text->print("Speed: " + std::to_string(9 - ((delay + 1) / 2)), 10, line1);
	if (paused)
	{
		text->print("X: Unpause", 10, line2);
		text->print("O: Next step", 200, line2);
	}
	else
		text->print("X: Pause", 10, line2);
	text->print("L/R: Decrease or increase speed", 200, line1);
	text->print("SELECT: Reset", 700, line2);


	SDL_RenderPresent(renderer);

	// Cleanup
	SDL_DestroyTexture(rendered_matrix);
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
