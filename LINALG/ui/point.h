#pragma once
#include "vec3d.h"
#include "SDL.h"
#include <vector>
#include <memory>

class point
{
public:
	point(vec3d v)
	{
		vector = v;
	}
	vec3d vector;
	std::vector<std::shared_ptr<point>> connections{};
	void link(std::shared_ptr<point>& p) { connections.emplace_back(p); };
};
