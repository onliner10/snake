#include "pch.h"
#include "Snake.h"
#include "ViewportHelper.h"
#include <algorithm>

Snake::Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth)
	:Drawable(renderer)
{
	this->_viewPort = viewPort;
	this->_currentDirection = LEFT;
	this->_segmentWidth = segmentWidth;
	this->_absSegmentWidth = scaleToWidth(_viewPort, _segmentWidth);
	this->_requestedDirection = NO_DIRECTION;

	const SnakeSegment startSegment = {scaleToViewPort(viewPort, 0.5, 0.8, 0.2, _segmentWidth), LEFT};
	this->_segments.push_back(startSegment);
}

void Snake::goLeft()
{
	if (this->_currentDirection != RIGHT && this->_currentDirection != LEFT)
	{
		_requestedDirection = LEFT;
	}
}

void Snake::goRight()
{
	if (this->_currentDirection != LEFT && this->_currentDirection != RIGHT)
	{
		_requestedDirection = RIGHT;
	}
}

void Snake::goDown()
{
	if (this->_currentDirection != UP && this->_currentDirection != DOWN)
	{
		_requestedDirection = DOWN;
	}
}

void Snake::goUp()
{
	if (this->_currentDirection != DOWN && this->_currentDirection != UP)
	{
		_requestedDirection = UP;
	}
}

int Snake::getLength()
{
	auto res = 0;
	for (auto segment = this->_segments.begin(); segment != this->_segments.end(); ++segment)
	{
		if (segment->direction == LEFT || segment->direction == RIGHT)
		{
			res += segment->rect.w;
		}
		else
		{
			res += segment->rect.h;
		}
	}
	return res;
}

void Snake::newSegment(Directions dir)
{
	const auto firstSegmentRect = this->_segments.front().rect;

	int x = firstSegmentRect.x;
	int y = firstSegmentRect.y;

	if (_currentDirection == RIGHT)
	{
		x += firstSegmentRect.w - _absSegmentWidth;
	}
	if (_currentDirection == DOWN)
	{
		y += firstSegmentRect.h - _absSegmentWidth;
	}

	const SnakeSegment newSegment = {
		SDL_Rect{x, y, _absSegmentWidth, _absSegmentWidth}, dir
	};

	this->_segments.insert(this->_segments.begin(), newSegment);
}


void Snake::ShrinkTail()
{
	const auto last = &this->_segments.back();
	const auto minDimension = std::min(last->rect.w, last->rect.h);
	if (minDimension <= 0)
	{
		this->_segments.erase(this->_segments.end() - 1);
		auto newLast = &this->_segments.back();
		enlargeSegment(newLast, minDimension);
	}
	else if (minDimension < _absSegmentWidth
		&& last->rect.x > this->_viewPort.x
		&& last->rect.x + last->rect.w < this->_viewPort.x + this->_viewPort.w
		&& last->rect.y > this->_viewPort.y
		&& last->rect.y + last->rect.h < this->_viewPort.y + this->_viewPort.h)
	{
		auto delta = abs(_absSegmentWidth - minDimension);
		this->_segments.erase(this->_segments.end() - 1);
		auto newLast = &this->_segments.back();
		shrinkSegment(newLast, delta);
	}
}

void Snake::MoveOutOfBoundsSegmentsIfAny()
{
	auto first = &this->_segments.front();
	// escape left side	
	if (first->rect.x < this->_viewPort.x)
	{
		auto xDiff = abs(this->_viewPort.x - first->rect.x);
		(&first->rect)->x = this->_viewPort.x;
		(&first->rect)->w -= xDiff;

		const SnakeSegment newSegment = {
			SDL_Rect{this->_viewPort.x + this->_viewPort.w - xDiff, first->rect.y, xDiff, _absSegmentWidth}, LEFT
		};

		this->_segments.insert(this->_segments.begin(), newSegment);
	}
		// escape right
	else if (first->rect.x + first->rect.w > this->_viewPort.x + this->_viewPort.w)
	{
		auto xDiff = abs(this->_viewPort.x + this->_viewPort.w - first->rect.x - first->rect.w);
		(&first->rect)->w -= xDiff;

		const SnakeSegment newSegment = {
			SDL_Rect{this->_viewPort.x, first->rect.y, xDiff, _absSegmentWidth}, RIGHT
		};

		this->_segments.insert(this->_segments.begin(), newSegment);
	}
		// escape up
	else if (first->rect.y < this->_viewPort.y)
	{
		auto yDiff = abs(this->_viewPort.y - first->rect.y);
		(&first->rect)->y = this->_viewPort.y;
		(&first->rect)->h -= yDiff;

		const SnakeSegment newSegment = {
			SDL_Rect{first->rect.x, this->_viewPort.y + this->_viewPort.h - yDiff, _absSegmentWidth, yDiff}, UP
		};

		this->_segments.insert(this->_segments.begin(), newSegment);
	}
		// escape down
	else if (first->rect.y + first->rect.h > this->_viewPort.y + this->_viewPort.h)
	{
		auto yDiff = abs(this->_viewPort.y + this->_viewPort.h - first->rect.y - first->rect.h);
		(&first->rect)->h -= yDiff;

		const SnakeSegment newSegment = {
			SDL_Rect{first->rect.x, this->_viewPort.y, _absSegmentWidth, yDiff}, DOWN
		};

		this->_segments.insert(this->_segments.begin(), newSegment);
	}
}

void Snake::tick()
{
	shrinkSegment(&this->_segments.back());
	enlargeSegment(&this->_segments.front());

	MoveOutOfBoundsSegmentsIfAny();

	auto firstRect = static_cast<SnakeSegment*const>(&this->_segments.front())->rect;
	// TODO: not really shure if a bug or feature
	if ((firstRect.w > 2 * _absSegmentWidth || firstRect.h > 2 * _absSegmentWidth) && _requestedDirection !=
		NO_DIRECTION)
	{
		newSegment(_requestedDirection);
		_currentDirection = _requestedDirection;
		_requestedDirection = NO_DIRECTION;
	}

	ShrinkTail();
}

void Snake::shrinkSegment(SnakeSegment* segment, int step)
{
	auto lastRect = &segment->rect;
	const auto lastDir = segment->direction;

	switch (lastDir)
	{
	case LEFT:
		lastRect->w -= step;
		break;
	case RIGHT:
		lastRect->x += step;
		lastRect->w -= step;
		break;
	case UP:
		lastRect->h -= step;
		break;
	case DOWN:
		lastRect->y += step;
		lastRect->h -= step;
		break;
	default:
		throw "No such direction found!";
	}
}

void Snake::enlargeSegment(SnakeSegment* segment, int step)
{
	auto frontRect = &segment->rect;
	const auto firstDir = segment->direction;

	switch (firstDir)
	{
	case LEFT:
		frontRect->x -= step;
		frontRect->w += step;
		break;
	case RIGHT:
		frontRect->w += step;
		break;
	case UP:
		frontRect->h += step;
		frontRect->y -= step;
		break;
	case DOWN:
		frontRect->h += step;
		break;
	default:
		throw "No such direction found!";
	}
}

void Snake::draw()
{
	SDL_SetRenderDrawColor(_renderer, 100, 0, 0, SDL_ALPHA_OPAQUE);
	for (auto segment : _segments)
	{
		SDL_RenderFillRect(_renderer, &segment.rect);
	}
}

bool Snake::collidesWith(SDL_Rect* rect)
{
	const auto first = this->_segments.front();
	return SDL_HasIntersection(rect, &first.rect);
}

Snake::~Snake()
{
}
