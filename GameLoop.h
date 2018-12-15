#pragma once
#include <SDL.h>
#include <memory>

class GameLoop
{
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
public:
	GameLoop(SDL_Window* window);
	~GameLoop();

	void start() const;
};

