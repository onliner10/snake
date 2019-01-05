#pragma once
#include "Drawable.h"
#include <vector>
#include "Apple.h"
#include "Collidable.h"

class ApplesLayer : Drawable
{
private:
	std::vector<Apple> _apples;
	Collidable _snake;
public:
	ApplesLayer(SDL_Renderer* renderer, Collidable snake);
	~ApplesLayer();
	void tick() override;
	void draw() override;
};

