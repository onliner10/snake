#include "pch.h"
#include "GameLoop.h"

GameLoop::GameLoop(SDL_Window* window)
{
	_window = window;
	_surface = SDL_GetWindowSurface(window);
}

GameLoop::~GameLoop()
= default;

void GameLoop::start() const
{
	SDL_FillRect(_surface, nullptr, SDL_MapRGB(_surface->format, 0x00, 0x00, 0x00));

	SDL_Rect rect = { 100, 100, 100, 100 };
	SDL_FillRect(_surface, &rect, SDL_MapRGB(_surface->format, 0xAA, 0xAA, 0xAA));

	SDL_UpdateWindowSurface(_window);

	SDL_Event event;
	auto shouldQuit = false;
	while (!shouldQuit)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				shouldQuit = true;
				break;

			case SDL_KEYUP:
				printf("Key release detected\n");
				break;

			default:
				break;
			}
		}
	}
}
