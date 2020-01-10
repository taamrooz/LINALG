#pragma once
#include "vector.h"
#include "SDL.h"
#include <vector>
#include <memory>

class point
{
public:
	point(vector v)
	{
		vector = v;
	}
	vector vector;
	std::vector<std::shared_ptr<point>> connections{};
	void link(std::shared_ptr<point>& p) { connections.emplace_back(p); };
};
