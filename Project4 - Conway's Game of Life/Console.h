#ifndef Console_h
#define Console_h
#include "TextHandler.h"
#include <list>

class Console {
public:
	Console(int x_ = 10, int y_ = 10, int w_ = 400, int h_ = 520, bool wrapping_ = false);
	~Console();
	void print(std::string text);
	void render();
private:
	int x, y, w, h;
	bool wrapping;
	TextHandler* text_handler;
	std::list<std::string> history;
};

#endif