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

class Snake : Drawable, public Collidable
{
private:
	Direction _currentDirection;
	Direction _requestedDirection;
	
	std::vector<SnakeSegment> _segments;
	float _segmentWidth;
	int _absSegmentWidth;
	int _toGrow;
	int _moveSpeed;
	SDL_Rect _viewPort;

	static void shrinkSegment(SnakeSegment* segment, int step);
	static void enlargeSegment(SnakeSegment* segment, int step);
	void newSegment(Directions dir);
	void ShrinkTail();
	void MoveOutOfBoundsSegmentsIfAny();
	void ShrinkTail(SnakeSegment *& last);
public:
	Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth = 0.02, int moveSpeed = 4);
	void goLeft();
	void goRight();
	void goDown();
	void goUp();
	void growBy(float step = 0.06);
	int getLength();

	void tick() override;
	void draw() override;
	bool collidesWith(SDL_Rect* rect) override;
	~Snake();
};

