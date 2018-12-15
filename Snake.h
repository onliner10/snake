#pragma once
#include <SDL.h>
#include "Direction.h"
#include <vector>

class Snake
{
private:
	SDL_Renderer* _renderer;
	SDL_Rect _viewPort{};
	Direction _currentDirection;
	std::vector<std::pair<SDL_Rect, Direction>> _segments;
	float _segmentWidth;
	int _absSegmentWidth;

	void shrinkSegment(std::pair<struct SDL_Rect, Directions>* segment, int step = 1);
	void enlargeSegment(std::pair<struct SDL_Rect, Directions>* segment, int step = 1);
	void newSegment(Directions dir);
public:
	Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth = 0.02);
	void goLeft();
	void goRight();
	void goDown();
	void goUp();
	
	void tick();
	void draw();
	~Snake();
};

