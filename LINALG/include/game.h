#pragma once
#include "SDL.h"

class Game
{
public:
	bool init();
private:
	SDL_Window* window_{};
	SDL_Renderer* renderer_{};
};
