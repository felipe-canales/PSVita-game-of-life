#include "TextHandler.h"
#include "Renderer.h"

const int CHAR_HEIGHT = 16;
const int CHAR_WIDTH = 12;

TextHandler::TextHandler()
{
	renderer = Renderer::GetInstance()->GetRenderer();
	font = IMG_LoadTexture(renderer, "assets/text2.png");
}

TextHandler::~TextHandler()
{
	SDL_DestroyTexture(font);
}

void TextHandler::print(const char* text, int x, int y)
{
	SDL_Rect c_src{ 0, 0, CHAR_WIDTH, CHAR_HEIGHT };
	SDL_Rect c_dest{ x, y, CHAR_WIDTH, CHAR_HEIGHT };
	while (*text != 0) {
		if (*text == '\n') {
			c_dest.x = x;
			c_dest.y += CHAR_HEIGHT;
			continue;
		}
		get_rect_of_char(*text, &c_src);
		SDL_RenderCopy(renderer, font, &c_src, &c_dest);
		c_dest.x += CHAR_WIDTH;
		++text;
	}
}

void TextHandler::print(std::string text, int x, int y)
{
	print(text.c_str(), x, y);
}

int TextHandler::get_line_height()
{
	return CHAR_HEIGHT;
}

int TextHandler::get_char_width()
{
	return CHAR_WIDTH;
}

void TextHandler::get_rect_of_char(char c, SDL_Rect* dest)
{
	if (c < 32 || c > 126) {
		dest->x = 31 * CHAR_WIDTH;
		dest->y = 2 * CHAR_HEIGHT;
	} else {
		dest->y = (((c + 1) / 32) - 1) * CHAR_HEIGHT;
		dest->x = (c % 32) * CHAR_WIDTH;
	}
}
