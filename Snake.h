#pragma once
#include <SDL.h>
#include "Direction.h"
#include <vector>
#include "Drawable.h"
#include "Collidable.h"

typedef struct
{
	SDL_Rect rect;
	Direction direction;
} SnakeSegment;

class Snake : Drawable, Collidable
{
private:
	Direction _currentDirection;
	Direction _requestedDirection;
	
	std::vector<SnakeSegment> _segments;
	float _segmentWidth;
	int _absSegmentWidth;
	SDL_Rect _viewPort;

	static void shrinkSegment(SnakeSegment* segment, int step = 6);
	static void enlargeSegment(SnakeSegment* segment, int step = 6);
	void newSegment(Directions dir);
	void ShrinkTail();
	void MoveOutOfBoundsSegmentsIfAny();
	void ShrinkTail(SnakeSegment *& last);
public:
	Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth = 0.02);
	void goLeft();
	void goRight();
	void goDown();
	void goUp();
	int getLength();

	void tick() override;
	void draw() override;
	bool collidesWith(SDL_Rect* rect) override;
	~Snake();
};

