#include "pch.h"
#include "GameLoop.h"
#include "Apple.h"
#include "ApplesLayer.h"
#include "GameLayer.h"
#include "GameoverLayer.h"

GameLoop::GameLoop(SDL_Window* window)
{
	_window = window;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	_gameOver = false;
}

GameLoop::~GameLoop()
= default;

void GameLoop::start() const
{
	const auto windowSurface = SDL_GetWindowSurface(_window);
	const SDL_Rect viewPort = { 0, 0, windowSurface->w, windowSurface->h};

	auto gameOverLayer = new GameoverLayer(_renderer, viewPort);
	auto gameLayer = new GameLayer(_renderer, viewPort);

	_activeLayer = gameLayer;
	gameLayer->onGameOver([=](int score) mutable
	{
		gameOverLayer->setScore(score);
		_gameOver = true;
	});
	gameOverLayer->onReset([=]() mutable 
	{
		gameLayer->reset();
		_gameOver = false;
	});

	auto shouldQuit = false;
	auto lastTick = std::chrono::system_clock::now();

	// 60 FPS
	const auto tickInterval = std::chrono::duration<double, std::milli>(1000 / 60);

	while (!shouldQuit)
	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> duration = (now - lastTick);
		if(duration < tickInterval)
			continue;
		lastTick = now;

		SDL_RenderClear(_renderer);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(_renderer, nullptr);

		if(_gameOver)
		{
			gameOverLayer->tick();
			gameLayer->draw();
			gameOverLayer->draw();
		} else
		{
			gameLayer->tick();
			gameLayer->draw();
		}

		SDL_RenderPresent(_renderer);
	}
}
