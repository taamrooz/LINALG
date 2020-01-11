#pragma once
#include "vec3d.h"
#include "SDL.h"
#include <vector>
#include <memory>

class point
{
public:
	point(vec3d v) : vector(v), w{ 1.0f } { }
	point(float x, float y, float z, float w) : vector(x, y, z), w{ w } {}
	vec3d vector;
	float w;
	std::vector<std::shared_ptr<point>> connections{};
	void link(std::shared_ptr<point>& p) { connections.emplace_back(p); };
};
