#pragma once
#include "SDL_render.h"

class vector
{
public:
	vector(float, float, float);
	vector& operator+=(const vector& v);
	vector& operator-=(const vector& v);
	vector& operator*=(const vector& v);
	vector& operator*=(float v);
	void multiply(float scalar);
	void render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height);
	float x, y, z;
};
