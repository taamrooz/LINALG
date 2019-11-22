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
	void scale_from_origin(double x, double y);
	void translate(double x, double y);
	void scale_from_point(double scale_x, double scale_y);
};
