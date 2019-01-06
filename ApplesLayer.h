#pragma once
#include "Drawable.h"
#include <vector>
#include "Apple.h"
#include "Collidable.h"
#include <functional>

class ApplesLayer : Drawable
{
private:
	Apple* _apple;
	SDL_Rect _viewPort;
	Collidable* _snake;
	float _appleWidth;
	std::function<void()> _onCollision;
public:
	ApplesLayer(SDL_Renderer* renderer, SDL_Rect viewPort, Collidable* snake, float appleWidth, std::function<void(void)> onCollision);
	~ApplesLayer();
	void tick() override;
	void draw() override;
};

