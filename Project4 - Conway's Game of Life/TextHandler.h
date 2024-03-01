#include "Game.h"
#include <string>

class TextHandler {
public:
	TextHandler();
	~TextHandler();
	void print(const char* text, int x, int y);
	void print(std::string text, int x, int y);
	int get_line_height();
	int get_char_width();
private:
	SDL_Texture* font;
	SDL_Renderer* renderer;
	void get_rect_of_char(char c, SDL_Rect* dest);
};