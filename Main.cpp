#include "pch.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "GameLoop.h"

int main(int argc, char* args[]) {
	fprintf(stdout, "Starting snake ...\n");

	const auto screenWidth = std::stoi(args[1]);
	const auto screenHeight = std::stoi(args[2]);

	fprintf(stdout, "Using resolution %dx%d", screenWidth, screenHeight);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	auto window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	
	if (window == nullptr) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	srand(time(NULL));

	const std::unique_ptr<GameLoop> gameLoop(new GameLoop(window));
	gameLoop->start();

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}