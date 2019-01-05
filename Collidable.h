#pragma once
#include <SDL.h>

class Collidable
{
public:
	virtual bool collidesWith(SDL_Rect* rects);
};

