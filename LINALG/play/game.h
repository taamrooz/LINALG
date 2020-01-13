#pragma once
#include "SDL.h"
#include <vector>
#include "object.h"
#include "vec3d.h"
#include "renderer.h"
#include "../models/ship.h"

class Game
{
public:
	
	bool init();
	ship ship_{};
	std::vector<std::shared_ptr<bullet>> bullets{};
private:
	int k_screen_width = 800;
	int k_screen_height = 600;
	SDL_Window* window_{};
	SDL_Renderer* renderer_{};
	renderer r_ = nullptr;
	void init_vectors();
	void make_ship_object();
	std::vector<object> objects_{};
	std::vector<vec3d> vectors_{};
	void shoot();
};
