#pragma once
#include "Drawable.h"
#include <string>
#include <SDL_ttf.h>
#include "ViewportHelper.h"
#include <sstream>
#include <functional>


class GameoverLayer :public Drawable
{
private:
	TTF_Font* _headerFont;
	SDL_Rect _viewport;
	TTF_Font* _mediumFont;
	TTF_Font* _smallFont;
	int _score;
	void centeredText(const char* text, TTF_Font* font, float height);
	std::function<void(void)> _onReset;
public:
	GameoverLayer(SDL_Renderer* renderer, SDL_Rect viewport);
	~GameoverLayer();
	void setScore(int score);
	void onReset(std::function<void(void)> handler);
	void tick() override;
	void draw() override;
};

