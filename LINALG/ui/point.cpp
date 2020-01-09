#include "point.h"

void point::render(SDL_Renderer* renderer_) const
{
	SDL_RenderDrawPoint(renderer_, get_render_x(), get_render_y());
}
