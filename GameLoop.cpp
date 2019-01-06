#include "pch.h"
#include "GameLoop.h"
#include "Apple.h"
#include "ApplesLayer.h"
#include "GameLayer.h"

GameLoop::GameLoop(SDL_Window* window)
{
	_window = window;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!TTF_WasInit()) { TTF_Init(); }
	_font = TTF_OpenFont("c:/windows/fonts/arial.ttf", 24);
}

GameLoop::~GameLoop()
= default;

void GameLoop::DrawDiagnosticsNumber(int snakeLength, int x, int y) const
{
	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, std::to_string(snakeLength).c_str(), White);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);	
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = textSurface->w; // controls the width of the rect
	Message_rect.h = textSurface->h; // controls the height of the rect

	SDL_RenderCopy(_renderer, textTexture, NULL, &Message_rect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void GameLoop::start() const
{
	const auto windowSurface = SDL_GetWindowSurface(_window);
	const SDL_Rect viewPort = { 0, 0, windowSurface->w, windowSurface->h};

	auto gameLayer = new GameLayer(_renderer, viewPort);
	
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

		gameLayer->tick();
		gameLayer->draw();

		DrawDiagnosticsNumber(1000 / duration.count(),100,10);

		SDL_RenderPresent(_renderer);
	}
}
