#pragma once
#include "Drawable.h"
#include "Snake.h"
#include "KeyboardListener.h"
#include "ApplesLayer.h"
#include <chrono>

class GameLayer: Drawable
{
private:
	SDL_Rect _viewPort;
	Snake* _snake;
	KeyboardListener<Snake>* _keyboard;
	ApplesLayer* _applesLayer;
public:
	GameLayer(SDL_Renderer* renderer, SDL_Rect viewPort);
	~GameLayer();
	void tick() override;
	void draw() override;
};

