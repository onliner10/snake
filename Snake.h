#pragma once
#include <SDL.h>
#include "Direction.h"
#include <vector>

typedef struct
{
	SDL_Rect rect;
	Direction direction;
} SnakeSegment;

class Snake
{
private:
	SDL_Renderer* _renderer;
	SDL_Rect _viewPort{};
	Direction _currentDirection;
	Direction _requestedDirection;
	
	std::vector<SnakeSegment> _segments;
	float _segmentWidth;
	int _absSegmentWidth;

	static void shrinkSegment(SnakeSegment* segment, int step = 5);
	static void enlargeSegment(SnakeSegment* segment, int step = 5);
	void newSegment(Directions dir);
public:
	Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth = 0.02);
	void goLeft();
	void goRight();
	void goDown();
	void goUp();
	int getLength();
	
	void tick();
	void draw();
	~Snake();
};

