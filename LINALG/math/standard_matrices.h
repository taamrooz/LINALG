#pragma once
#include "matrix.h"
inline auto scaling_matrix = [](double x, double y){
	matrix return_matrix{};

	std::vector<float> row{};
	row.emplace_back(x);
	row.emplace_back(0);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(y);
	return_matrix.numbers.emplace_back(row);
	return return_matrix;
};

inline auto translation_matrix = [](double x, double y) {
	matrix return_matrix{};

	std::vector<float> row{};
	row.emplace_back(1);
	row.emplace_back(0);
	row.emplace_back(x);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(1);
	row.emplace_back(y);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(1);
	return_matrix.numbers.emplace_back(row);
	return return_matrix;
};

inline auto rotation_matrix = [](double degrees) {
	matrix return_matrix{};

	std::vector<float> row{};
	row.emplace_back(cos(degrees));
	row.emplace_back(-1 * sin(degrees));
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(sin(degrees));
	row.emplace_back(cos(degrees));
	return_matrix.numbers.emplace_back(row);
	return return_matrix;
};