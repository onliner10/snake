#include "pch.h"
#include "GameoverLayer.h"

GameoverLayer::GameoverLayer(SDL_Renderer* renderer, SDL_Rect viewport)
	:Drawable(renderer)
{
	if (!TTF_WasInit()) { TTF_Init(); }
	_viewport = viewport;
	_headerFont = TTF_OpenFont("c:/windows/fonts/arial.ttf", _viewport.h * 0.1);
	_mediumFont = TTF_OpenFont("c:/windows/fonts/arial.ttf", _viewport.h * 0.06);
	_smallFont = TTF_OpenFont("c:/windows/fonts/arial.ttf", _viewport.h * 0.03);
	_score = 0;
	_onReset = []() {};
}


GameoverLayer::~GameoverLayer()
{
}

void GameoverLayer::setScore(int score)
{
	_score = score;
}

void GameoverLayer::onReset(std::function<void()> handler)
{
	_onReset = handler;
}

void GameoverLayer::tick()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_SPACE)
			{
				_onReset();
			}
			break;
		default:
			break;
		}
	}
}

void GameoverLayer::centeredText(const char* text, TTF_Font* font, float height = 0.5)
{
	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, White);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = _viewport.x + (_viewport.w / 2) - textSurface->w / 2;  //controls the rect's x coordinate 
	Message_rect.y = _viewport.y + _viewport.h * height; // controls the rect's y coordinte
	Message_rect.w = textSurface->w; // controls the width of the rect
	Message_rect.h = textSurface->h; // controls the height of the rect

	SDL_RenderCopy(_renderer, textTexture, NULL, &Message_rect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void GameoverLayer::draw()
{
	std::stringstream scoreSs;
	scoreSs << "Your score: ";
	scoreSs << _score;

	centeredText("Game over!",_headerFont,0.3);
	centeredText(scoreSs.str().c_str(),_mediumFont,0.41);
	centeredText("Press space to play again",_smallFont,0.7);
}
