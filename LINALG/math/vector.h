#pragma once
#include "SDL_render.h"

class vector
{
public:
	vector();
	vector(float, float, float);
	vector& operator+=(const vector& v);
	vector& operator-=(const vector& v);
	vector& operator*=(const vector& v);
	vector& operator*=(float v);
	vector& operator/=(float v);
	vector operator+(const vector& v) const;
	vector operator-(const vector& v) const;
	vector operator*(const vector& v) const;
	vector operator*(float v) const;
	vector operator/(float v) const;
	vector cross(const vector& other) const;
	float length() const;
	void normalize();
	void multiply(float scalar);
	void render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height);
	float x, y, z;
};
