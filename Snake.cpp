#include "pch.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>

int main(int argc, char* args[]) {
	const auto screenWidth = std::stoi(args[1]);
	const auto screenHeight = std::stoi(args[2]);
	
	printf("Starting snake ...\n");
	printf("Using resolution %dx%d", screenWidth, screenHeight);

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	SDL_Rect rect = { 100, 100, 100, 100 };
	SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xAA,0xAA, 0xAA));
	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	auto shouldQuit = false;
	while(!shouldQuit)
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

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
