#pragma once
#include <SDL.h>
#include <memory>
#include <SDL_ttf.h>
#include "Snake.h"
#include "KeyboardListener.h"
#include <chrono>
#include <string>
#include "GameLayer.h"
#include "GameoverLayer.h"

class GameLoop
{
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	mutable Drawable* _activeLayer;
	mutable bool _gameOver;
public:
	GameLoop(SDL_Window* window);
	~GameLoop();

	void start() const;
};

