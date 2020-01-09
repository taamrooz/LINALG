#pragma once
#include "renderable.h"
#include "SDL.h"
#include <vector>
#include <memory>

class point : public renderable
{
public:
	point(float x, float y, float z, int screen_width, int screen_height) : renderable(x, y, z, screen_width, screen_height) {}
	void render(SDL_Renderer* renderer_) const;
	std::vector<std::shared_ptr<point>> connections{};
};
