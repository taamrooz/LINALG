#pragma once
#include "SDL_render.h"

class vector
{
public:
	void add(const vector* v);
	void subtract(const vector* v);
	void multiply(int scalar);
	void render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height);
	int x;
	int y;
};
