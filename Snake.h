#pragma once
#include <SDL.h>
#include "Direction.h"

class Snake
{
private:
	SDL_Renderer* _renderer;
	SDL_Rect _viewPort{};
	Direction _currentDirection;
public:
	Snake(SDL_Renderer* renderer, SDL_Rect viewPort);
	void goLeft();
	void goRight();
	void goDown();
	void goUp();

	void draw();
	~Snake();
};

