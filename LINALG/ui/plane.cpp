#include "plane.h"

plane::plane(std::vector<std::shared_ptr<point>> points)
{
	this->points = points;
}

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

void plane::link_points()
{
	for(auto i = 0; i+1 < points.size(); ++i)
	{
		points[i]->link(points[i+1]);
	}
	points[0]->link(points[points.size()-1]);
}
