#include "pch.h"
#include "Apple.h"

Apple::Apple(SDL_Renderer* renderer, int x, int y) 
	:Drawable(renderer)
{
	this->_x = x;
	this->_y = y;
}

Apple::~Apple()
{
}

void Apple::tick()
{
}

void Apple::draw()
{
	filledCircleColor(_renderer, _x, _y, 8, 0xff00ff00);
	aacircleColor(_renderer, _x, _y, 7, 0xff00ff00);
	aacircleColor(_renderer, _x, _y, 8, 0xff00ff00);
}
