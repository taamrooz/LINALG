#include "renderer.h"
#include "SDL.h"

renderer::renderer(SDL_Renderer* renderer)
{
	renderer_ = renderer;
}

void renderer::render(object& o, bool x_axis, bool y_axis, bool z_axis)
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (auto& plane : o.planes)
	{
		for (auto& point : plane->points)
		{
			for(auto& connection : point->connections)
			SDL_RenderDrawLineF(renderer_, point->vector.x, point->vector.z,
				connection->vector.x, connection->vector.z);
		}
	}
}
