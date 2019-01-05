#include "pch.h"
#include "ApplesLayer.h"



ApplesLayer::ApplesLayer(SDL_Renderer* renderer, Collidable snake): Drawable(renderer)
{
	this->_snake = snake;
}

ApplesLayer::~ApplesLayer()
{
}

void ApplesLayer::tick()
{
}

void ApplesLayer::draw()
{
}
