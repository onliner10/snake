#pragma once
#include <SDL.h>

class Drawable
{
protected:
	SDL_Renderer* _renderer;
public:
	Drawable(SDL_Renderer* renderer);
	virtual void tick();
	virtual void draw();
};

