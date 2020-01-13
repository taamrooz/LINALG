#pragma once
#include "object.h"

class renderer
{
private:
	SDL_Renderer* renderer_;
public:
	renderer(SDL_Renderer* renderer);
	void render(object& o);
};
