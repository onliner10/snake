#include "pch.h"
#include "Apple.h"

Apple::Apple(SDL_Renderer* renderer, int x, int y, int radius) 
	:Drawable(renderer)
{
	this->_x = x;
	this->_y = y;
	this->_radius = radius;
}

Apple::~Apple()
{
}

void Apple::tick()
{
}

void Apple::draw()
{
	filledCircleColor(_renderer, _x, _y, _radius, 0xff00ff00);
	aacircleColor(_renderer, _x, _y, _radius - 1, 0xff00ff00);
	aacircleColor(_renderer, _x, _y, _radius, 0xff00ff00);
}

SDL_Rect Apple::collisionRect()
{
	return  SDL_Rect{ _x - _radius, _y - _radius, 2 * _radius, 2 * _radius };
}
