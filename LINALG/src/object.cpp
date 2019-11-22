#include "object.h"

void object::add_point(std::shared_ptr<point> p)
{
	points.emplace_back(p);
}

void object::render(SDL_Renderer* renderer_)
{
	for (const auto& point : points)
	{
		point->render(renderer_);
		for (auto connection : point->connections)
		{
			SDL_RenderDrawLine(renderer_, connection->get_render_x(), connection->get_render_y(), point->get_render_x(), point->get_render_y());
		}
	}
}

void object::scale_from_origin()
{
	
}

void object::translate()
{
}

void object::scale_from_point()
{
}
