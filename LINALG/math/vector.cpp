#include "vector.h"
#include "SDL.h"

vector::vector(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

vector& vector::operator+=(const vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vector& vector::operator-=(const vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vector& vector::operator*=(const vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vector& vector::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

void vector::multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void vector::render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height)
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer_, k_screen_width / 2, k_screen_height / 2, k_screen_width / 2 + x, k_screen_height / 2 + -1 * y);
}
