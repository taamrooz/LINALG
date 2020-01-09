#pragma once
#include "SDL.h"
#include <vector>
#include "object.h"
#include "vector.h"
#include "renderable.h"

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
