#include "pch.h"
#include "GameLoop.h"
#include "Snake.h"
#include "KeyboardListener.h"

GameLoop::GameLoop(SDL_Window* window)
{
	_window = window;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

GameLoop::~GameLoop()
= default;

void GameLoop::start() const
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(_renderer, nullptr);

	const auto windowSurface = SDL_GetWindowSurface(_window);
	const SDL_Rect viewPort = { 0, 0, windowSurface->w, windowSurface->h};

	auto snake = new Snake(_renderer, viewPort);
	auto keyboardListener = new KeyboardListener<Snake>(snake);
	keyboardListener->registerKey(SDLK_DOWN, [](Snake* s) { s->goDown();});
	keyboardListener->registerKey(SDLK_UP, [](Snake* s) { s->goUp(); });
	keyboardListener->registerKey(SDLK_RIGHT, [](Snake* s) { s->goRight(); });
	keyboardListener->registerKey(SDLK_LEFT, [](Snake* s) { s->goLeft(); });

	snake->draw();

	SDL_RenderPresent(_renderer);
	
	SDL_Event event;
	auto shouldQuit = false;
	while (!shouldQuit)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				keyboardListener->dispatch(event.key.keysym.sym);
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
