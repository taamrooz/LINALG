#pragma once
#include "renderable.h"
#include "SDL.h"

class grid
{
public:
	grid(int width, int height);
	void Render(SDL_Renderer* renderer);
	int screen_width;
	int screen_height;
private:
};
