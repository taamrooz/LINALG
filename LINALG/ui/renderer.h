#pragma once
#include "object.h"

class renderer
{
private:
	SDL_Renderer* renderer_;
public:
	renderer(SDL_Renderer* renderer);
	void render_front(object& o);
	void render_side(object& o);
	void render_top(object& o);
};
