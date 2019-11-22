#include "vector.h"
#include "SDL.h"

void vector::add(const vector* v)
{
	x += v->x;
	y += v->y;
}

void vector::subtract(const vector* v)
{
	x -= v->x;
	y -= v->y;
}

void vector::multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void vector::render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height)
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer_, k_screen_width / 2, k_screen_height / 2, k_screen_width / 2 + x, k_screen_height / 2 + -1 * y);
}
