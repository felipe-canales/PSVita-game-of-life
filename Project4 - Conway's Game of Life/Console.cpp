#include "Console.h"

const int HISTORY_MAX_SIZE = 100;

Console::Console(int x_, int y_, int w_, int h_, bool wrapping_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
	wrapping = wrapping_;
	text_handler = new TextHandler();
}

Console::~Console()
{
	delete text_handler;
}

void Console::print(std::string text)
{
	history.push_front(text);
	if (history.size() > HISTORY_MAX_SIZE)
		history.pop_back();
}

void Console::render()
{
	int cursor = 0;
	int height = text_handler->get_line_height();
	int width = text_handler->get_char_width();
	for (auto line : history) {
		if (cursor * height > h)
			break;
		if (!wrapping)
			text_handler->print(line, x, y + (cursor * height));
		else {
			int line_chars = w / width;
			int i = 0;
			while (line.size() > line_chars) {
				text_handler->print(line.substr(0, line_chars), x, y + (cursor * height));
				line = line.substr(line_chars);
				++cursor;
			}
			text_handler->print(line, x, y + (cursor * height));
		}
		++cursor;
	}
}
