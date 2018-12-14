#pragma once
#include <SDL.h>
#include <memory>

class GameLoop
{
private:
	SDL_Surface* _surface;
	SDL_Window* _window;
public:
	GameLoop(SDL_Window* window);
	~GameLoop();

	void start() const;
};

