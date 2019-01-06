#include "pch.h"
#include "ApplesLayer.h"
#include "ViewportHelper.h"


ApplesLayer::ApplesLayer(SDL_Renderer* renderer, SDL_Rect viewPort, Collidable* snake, float appleWidth,
                         std::function<void(void)> onCollision): Drawable(renderer)
{
	this->_snake = snake;
	this->_viewPort = viewPort;
	this->_appleWidth = appleWidth;
	this->_onCollision = onCollision;
	this->_apple = nullptr;
}

ApplesLayer::~ApplesLayer()
{
}

void ApplesLayer::tick()
{
	const auto absApplewidth = scaleToWidth(_viewPort, _appleWidth);
	while (_apple == nullptr)
	{
		auto x = rand() % (_viewPort.w - _viewPort.x - 2*absApplewidth) + _viewPort.x;
		auto y = rand() % (_viewPort.h - _viewPort.y - 2*absApplewidth) + _viewPort.y;
		_apple = new Apple(_renderer, x, y, absApplewidth);

		if (_snake->collidesWith(&_apple->collisionRect()))
		{
			delete _apple;
			_apple = nullptr;
			continue;
		}

		break;
	}

	_apple->tick();
	if (_snake->collidesWith(&_apple->collisionRect()))
	{
		_onCollision();
		delete _apple;
		_apple = nullptr;
	}
}

void ApplesLayer::draw()
{
	if (_apple != nullptr)
	{
		_apple->draw();
	}
}
