#pragma once
#include <vector>
#include <memory>
#include "point.h"

class plane
{
public:
	plane(std::vector<std::shared_ptr<point>> points);
	std::vector<std::shared_ptr<point>> points{};
	void add_point(std::shared_ptr<point> p);
	void add_points(std::vector<std::shared_ptr<point>> points);
	void link_points();
	void move_object(vec3d& v);
};
