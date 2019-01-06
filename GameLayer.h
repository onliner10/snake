#pragma once
#include "Drawable.h"
#include "Snake.h"
#include "KeyboardListener.h"
#include "ApplesLayer.h"
#include <chrono>
#include "GameLoop.h"

class GameLayer: public Drawable
{
private:
	SDL_Rect _viewPort;
	Snake* _snake;
	int _score;
	KeyboardListener<Snake>* _keyboard;
	ApplesLayer* _applesLayer;
	std::function<void(int)> _onGameOver;
	TTF_Font* _font;
public:
	GameLayer(SDL_Renderer* renderer, SDL_Rect viewPort);
	~GameLayer();
	void onGameOver(std::function<void(int)> handler);
	void reset();
	void tick() override;
	void draw() override;
};

