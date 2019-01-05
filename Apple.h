#pragma once
#include "Drawable.h"
#include "SDL2_gfxPrimitives.h"

class Apple : Drawable
{
private:
	int _x, _y;
public:
	Apple(SDL_Renderer* renderer, int x, int y);
	~Apple();
	void tick() override;
	void draw() override;
};

