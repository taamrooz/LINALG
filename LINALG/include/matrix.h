#pragma once
#include "SDL.h"
#include "vector.h"
#include <vector>

class matrix
{
public:
	void add(const matrix* m);
	void subtract(const matrix* m);
	void multiply_vector(vector* v);
	void multiply_matrix(matrix* m);
	void render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height);
	std::vector<std::vector<double>> numbers{};
};