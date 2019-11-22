#include "grid.h"
#include "SDL.h"

grid::grid(int width, int height)
{
	screen_width = width;
	screen_height = height;
}

void grid::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 0, screen_height/2, screen_width, screen_height/2);
	SDL_RenderDrawLine(renderer, screen_width/2, 0, screen_width / 2, screen_height);
}

