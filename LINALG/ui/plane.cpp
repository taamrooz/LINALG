#include "plane.h"

void plane::add_point(std::shared_ptr<point> p)
{
	points.emplace_back(p);
}

void plane::add_points(std::vector<std::shared_ptr<point>> ps)
{
	for (auto& p : ps)
	{
		points.emplace_back(p);
	}
}