#pragma once
#include <SDL.h>
#include <memory>
#include <SDL_ttf.h>

class GameLoop
{
private:
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	TTF_Font* _font;
public:
	GameLoop(SDL_Window* window);
	~GameLoop();
	void DrawDiagnosticsNumber(int snakeLength) const;

	void start() const;
};

