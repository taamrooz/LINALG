#pragma once
#include "vector.h"
#include <vector>

class matrix
{
public:
	matrix() = default;
	matrix(int rows, int columns);
	void add(const matrix* m);
	void subtract(const matrix* m);
	matrix& multiply_vector(vector* v);
	matrix* multiply_matrix(matrix* m);
	std::vector<std::vector<float>> numbers{};
};