#pragma once
#include "point.h"
#include <vector>
#include "SDL.h"
#include <unordered_map>

class object
{
public:
	std::vector<std::shared_ptr<point>> points{};
	void add_point(std::shared_ptr<point> p);
	void render(SDL_Renderer* renderer_);
	void scale_from_origin();
	void translate();
	void scale_from_point();
};
