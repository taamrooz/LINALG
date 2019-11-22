#pragma once
#include "SDL.h"
#include "vector.h"
#include <vector>

class matrix
{
public:
	matrix() = default;
	matrix(int rows, int columns);
	void add(const matrix* m);
	void subtract(const matrix* m);
	matrix* multiply_vector(vector* v);
	matrix* multiply_matrix(matrix* m);
	void render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height);
	std::vector<std::vector<double>> numbers{};
};