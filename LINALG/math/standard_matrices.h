#pragma once
#include "matrix.h"

inline auto scaling_matrix_3d = [](double x, double y, double z) {
	matrix return_matrix{};

	std::vector<float> row{};
	row.emplace_back(x);
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(0);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(y);
	row.emplace_back(0);
	row.emplace_back(0);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(z);
	row.emplace_back(0);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(1);
	return_matrix.numbers.emplace_back(row);
	return return_matrix;
};

inline auto translation_matrix_3d = [](float x, float y, float z) {
	matrix return_matrix{};

	std::vector<float> row{};
	row.emplace_back(1);
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(x);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(1);
	row.emplace_back(0);
	row.emplace_back(y);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(1);
	row.emplace_back(z);
	return_matrix.numbers.emplace_back(row);
	row.clear();
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(0);
	row.emplace_back(1);
	return_matrix.numbers.emplace_back(row);
	return return_matrix;
};

inline auto rotation_matrix_3d_x = [](float degrees) {
	matrix return_matrix{4,4};
	return_matrix.numbers[0][0] = 1; return_matrix.numbers[0][1] = 0;             return_matrix.numbers[0][2] = 0;              return_matrix.numbers[0][3] = 0;
	return_matrix.numbers[1][0] = 0; return_matrix.numbers[1][1] = cosf(degrees); return_matrix.numbers[1][2] = -sinf(degrees); return_matrix.numbers[1][3] = 0;
	return_matrix.numbers[2][0] = 0; return_matrix.numbers[2][1] = sinf(degrees); return_matrix.numbers[2][2] = cosf(degrees);  return_matrix.numbers[2][3] = 0;
	return_matrix.numbers[3][0] = 0; return_matrix.numbers[3][1] = 0;             return_matrix.numbers[3][2] = 0;              return_matrix.numbers[3][3] = 1;
	return return_matrix;
};

inline auto rotation_matrix_3d_y = [](float degrees) {
	matrix return_matrix{ 4,4 };
	return_matrix.numbers[0][0] = cosf(degrees);  return_matrix.numbers[0][1] = 0; return_matrix.numbers[0][2] = sinf(degrees); return_matrix.numbers[0][3] = 0;
	return_matrix.numbers[1][0] = 0;              return_matrix.numbers[1][1] = 1; return_matrix.numbers[1][2] = 0;             return_matrix.numbers[1][3] = 0;
	return_matrix.numbers[2][0] = -sinf(degrees); return_matrix.numbers[2][1] = 0; return_matrix.numbers[2][2] = cosf(degrees); return_matrix.numbers[2][3] = 0;
	return_matrix.numbers[3][0] = 0;			  return_matrix.numbers[3][1] = 0; return_matrix.numbers[3][2] = 0;             return_matrix.numbers[3][3] = 1;
	return return_matrix;
};

inline auto rotation_matrix_3d_z = [](float degrees) {
	matrix return_matrix{ 4,4 };
	return_matrix.numbers[0][0] = cosf(degrees);  return_matrix.numbers[0][1] = sinf(degrees);  return_matrix.numbers[0][2] = 0; return_matrix.numbers[0][3] = 0;
	return_matrix.numbers[1][0] = -sinf(degrees); return_matrix.numbers[1][1] = cosf(degrees);  return_matrix.numbers[1][2] = 0; return_matrix.numbers[1][3] = 0;
	return_matrix.numbers[2][0] = 0;              return_matrix.numbers[2][1] = 0;              return_matrix.numbers[2][2] = 1; return_matrix.numbers[2][3] = 0;
	return_matrix.numbers[3][0] = 0;			  return_matrix.numbers[3][1] = 0;              return_matrix.numbers[3][2] = 0; return_matrix.numbers[3][3] = 1;
	return return_matrix;
};

inline auto scaling_matrix_2d = [](double x, double y){
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

inline auto translation_matrix_2d = [](double x, double y) {
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

inline auto rotation_matrix_2d = [](double degrees) {
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