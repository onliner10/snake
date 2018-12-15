#include "pch.h"
#include "Snake.h"
#include <cstdio>
#include "ViewportHelper.h"

Snake::Snake(SDL_Renderer* renderer, SDL_Rect viewPort, float segmentWidth)
{
	this->_renderer = renderer;
	this->_viewPort = viewPort;
	this->_currentDirection = LEFT;
	this->_segmentWidth = segmentWidth;
	this->_absSegmentWidth = scaleToWidth(_viewPort, _segmentWidth);
	this->_requestedDirection = NO_DIRECTION;

	const auto startSegment = std::make_pair(scaleToViewPort(viewPort, 0.5, 0.5, 0.1, _segmentWidth), LEFT);

	this->_segments.push_back(startSegment);
}

void Snake::goLeft()
{
	_requestedDirection = LEFT;
}

void Snake::goRight()
{
	_requestedDirection = RIGHT;
}

void Snake::goDown()
{
	_requestedDirection = DOWN;
}

void Snake::goUp()
{
	_requestedDirection = UP;
}

void Snake::newSegment(Directions dir)
{
	const auto firstSegmentRect = this->_segments.front().first;
	
	int x = firstSegmentRect.x;
	int y = firstSegmentRect.y;

	if(_currentDirection == RIGHT)
	{
		x += firstSegmentRect.w - _absSegmentWidth;
	}
	if(_currentDirection == DOWN)
	{
		y += firstSegmentRect.h - _absSegmentWidth;
	}

	const auto newSegment = std::make_pair(
		SDL_Rect{ x, y, _absSegmentWidth, _absSegmentWidth}, dir
	);

	this->_segments.insert(this->_segments.begin(), newSegment);
}


void Snake::tick()
{
	auto last = &this->_segments.back();
		
	shrinkSegment(last);
	if (last->first.h <= _absSegmentWidth && last->first.w <= _absSegmentWidth)
		this->_segments.erase(this->_segments.end() - 1);

	auto first = &this->_segments.front();
	auto firstRect = first->first;
	enlargeSegment(first);

	// TODO: not really shure if a bug or feature
	if ((firstRect.w > 2 * _absSegmentWidth || firstRect.h > 2 * _absSegmentWidth) && _requestedDirection != NO_DIRECTION)
	{
		newSegment(_requestedDirection);
		_currentDirection = _requestedDirection;
		_requestedDirection = NO_DIRECTION;
	}

}

void Snake::shrinkSegment(std::pair<struct SDL_Rect, Directions>* segment, int step)
{
	auto lastRect = &segment->first;
	auto lastDir = segment->second;

	switch(lastDir)
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

void Snake::enlargeSegment(std::pair<struct SDL_Rect, Directions>* segment, int step)
{
	auto frontRect = &segment->first;
	auto firstDir = segment->second;

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
		SDL_RenderFillRect(_renderer, &segment.first);
	}
}

Snake::~Snake()
{
}
