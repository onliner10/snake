#pragma once
#include <SDL.h>

inline SDL_Rect scaleToViewPort(SDL_Rect absViewport, float x, float y, float w, float h)
{
	const auto absoluteWidth = absViewport.w - absViewport.x;
	const auto absoluteHeight = absViewport.h - absViewport.y;
	return {
		static_cast<int>(absViewport.x + x * absoluteWidth),
		static_cast<int>(absViewport.y + y * absoluteHeight),
		static_cast<int>(w * absoluteWidth),
		static_cast<int>(h * absoluteWidth)
	};
}


inline int scaleToWidth(SDL_Rect absViewport, float v)
{
	const auto absoluteWidth = absViewport.w - absViewport.x;
	return static_cast<int>(v * absoluteWidth);
}