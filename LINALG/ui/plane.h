#pragma once
#include <vector>
#include <memory>
#include "point.h"

class plane
{
public:
	std::vector<std::shared_ptr<point>> points{};
	void add_point(std::shared_ptr<point> p);
	void add_points(std::vector<std::shared_ptr<point>> points);
};
