#include "pch.h"
#include "GameLayer.h"

GameLayer::GameLayer(SDL_Renderer* renderer, SDL_Rect viewPort)
	:Drawable(renderer)
{
	this->_viewPort = viewPort;
	reset();

	_onGameOver = [](int x) {};
}


GameLayer::~GameLayer()
{
	delete _snake;
	delete _keyboard;
	delete _applesLayer;
}

void GameLayer::onGameOver(std::function<void(int)> handler)
{
	_onGameOver = handler;
}

void GameLayer::reset()
{
	if (_snake != nullptr) delete _snake;
	if (_keyboard != nullptr) delete _keyboard;
	if(_applesLayer != nullptr) delete _applesLayer;

	this->_snake = new Snake(_renderer, _viewPort);
	_snake->onSelfCollision([this]()
	{
		_onGameOver(_score);
	});

	_keyboard = new KeyboardListener<Snake>(_snake);
	_keyboard->registerKey(SDLK_DOWN, [](Snake* s) { s->goDown(); });
	_keyboard->registerKey(SDLK_UP, [](Snake* s) { s->goUp(); });
	_keyboard->registerKey(SDLK_RIGHT, [](Snake* s) { s->goRight(); });
	_keyboard->registerKey(SDLK_LEFT, [](Snake* s) { s->goLeft(); });

	_applesLayer = new ApplesLayer(_renderer, _viewPort, _snake, 0.01f, [this]()
	{
		_score++;
		_snake->growBy();
	});
	_score = 0;
}

void GameLayer::tick()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			_keyboard->dispatch(event.key.keysym.sym);
			break;
		default:
			break;
		}
	}

	_snake->tick();
	_applesLayer->tick();
}

void GameLayer::draw()
{
	_snake->draw();
	_applesLayer->draw();
}
