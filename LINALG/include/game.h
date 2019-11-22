#pragma once
#include "SDL.h"
#include "renderable.h"
#include <vector>
#include "vector.h"
#include "object.h"

class Game
{
public:
	bool init();
private:
	int k_screen_width = 800;
	int k_screen_height = 600;
	SDL_Window* window_{};
	SDL_Renderer* renderer_{};
	void draw_grid();
	void init_vectors();
	void make_object();
	std::vector<renderable> renderables_{};
	std::vector<vector> vectors_{};
	object o{};
};
