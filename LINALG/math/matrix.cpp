#include "matrix.h"

matrix::matrix(int rows, int columns)
{
	for (int i = 0; i < rows; ++i)
		numbers.emplace_back(std::vector<float>(columns));
}

void matrix::add(const matrix* m)
{
	if (numbers.size() != m->numbers.size())
		return;

	auto row_counter = 0;
	for (auto& row : numbers)
	{
		if (row.size() != m->numbers[row_counter].size())
			return;

		auto column_counter = 0;
		for (auto& column : row)
		{
			column += m->numbers[row_counter][column_counter];
			++column_counter;
		}
		++row_counter;
	}
}

void matrix::subtract(const matrix* m)
{
	if (numbers.size() != m->numbers.size())
		return;

	auto row_counter = 0;
	for (auto& row : numbers)
	{
		if (row.size() != m->numbers[row_counter].size())
			return;

		auto column_counter = 0;
		for (auto& column : row)
		{
			column -= m->numbers[row_counter][column_counter];
			++column_counter;
		}
		++row_counter;
	};
}

matrix& matrix::multiply_vector(vector* v)
{
	matrix temp_matrix{};
	for (auto& row : numbers)
	{
		if (row.size() != 3)
			return *this;
		temp_matrix.numbers.emplace_back(std::vector<float>{row[0] * v->x + row[1] * v->y + row[2] * v->z});
	}
	numbers = temp_matrix.numbers;
	return *this;
}

matrix* matrix::multiply_matrix(matrix* m)
{
	if (!numbers.empty())
		if (numbers[0].size() != m->numbers.size())
			return nullptr;

	auto row_counter = 0;
	matrix temp_matrix{ static_cast<int>(numbers.size()), static_cast<int>(m->numbers[0].size()) };
	for (auto& row : numbers)
	{
		auto column_counter = 0;
		while (column_counter < m->numbers.front().size()) {
			float mult_total = 0;
			auto row_in_arg = 0;
			for (auto& column : row)
			{
				mult_total += column * m->numbers[row_in_arg][column_counter];
				++row_in_arg;
			}
			temp_matrix.numbers[row_counter][column_counter] = mult_total;
			++column_counter;
		}
		++row_counter;
	}
	numbers = temp_matrix.numbers;
	return this;
}
