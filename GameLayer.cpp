#include "pch.h"
#include "GameLayer.h"

GameLayer::GameLayer(SDL_Renderer* renderer, SDL_Rect viewPort)
	:Drawable(renderer)
{
	if (!TTF_WasInit()) { TTF_Init(); }
	this->_viewPort = viewPort;
	this->_font = TTF_OpenFont("c:/windows/fonts/arial.ttf", viewPort.h * 0.03);
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
	delete _snake;
	delete _keyboard;
	delete _applesLayer;

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

	SDL_Color White = { 255, 255, 255 };  

	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, std::to_string(_score).c_str(), White);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_Rect Message_rect;
	Message_rect.x = _viewPort.x + 0.01 * _viewPort.w; 
	Message_rect.y = _viewPort.y + 0.01 * _viewPort.h; 
	Message_rect.w = textSurface->w; 
	Message_rect.h = textSurface->h; 

	SDL_RenderCopy(_renderer, textTexture, NULL, &Message_rect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
