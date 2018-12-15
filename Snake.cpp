#include "pch.h"
#include "Snake.h"
#include <cstdio>

Snake::Snake(SDL_Renderer* renderer, SDL_Rect viewPort)
{
	this->_renderer = renderer;
	this->_viewPort = viewPort;
}

void Snake::goLeft()
{
	printf("GO LEFT");
	_currentDirection = LEFT;
}

void Snake::goRight()
{
	printf("GO RIGHT");
	_currentDirection = RIGHT;
}

void Snake::goDown()
{
	printf("GO DOWN");
	_currentDirection = DOWN;
}

void Snake::goUp()
{
	printf("GO UP");
	_currentDirection = UP;
}

void Snake::draw()
{
	SDL_SetRenderDrawColor(_renderer, 100, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect rect = {_viewPort.x + 100, _viewPort.y + 100, 25, 25};
	SDL_RenderFillRect(_renderer, &rect);
}

Snake::~Snake()
{
}
