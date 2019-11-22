#include "matrix.h"

void matrix::add(const matrix* m)
{
	if (numbers.size() != m->numbers.size())
		return;

	int row_counter = 0;
	for (auto row : numbers)
	{
		if (row.size() != m->numbers[row_counter].size())
			return;

		int column_counter = 0;
		for (auto column : row)
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

	int row_counter = 0;
	for (auto row : numbers)
	{
		if (row.size() != m->numbers[row_counter].size())
			return;

		int column_counter = 0;
		for (auto column : row)
		{
			column -= m->numbers[row_counter][column_counter];
			++column_counter;
		}
		++row_counter;
	};
}

void matrix::multiply_vector(vector* v)
{
	matrix temp_matrix{};
	for (auto row : numbers)
	{
		if (row.size() != 2)
			return;
		temp_matrix.numbers.emplace_back(
			row[0] * v->x + row[1] * v->y
		);
	}
	numbers = temp_matrix.numbers;
}

void matrix::multiply_matrix(matrix* m)
{
	if (!numbers.empty())
		if (numbers[0].size() != m->numbers.size())
			return;

	int row_counter = 0;
	matrix temp_matrix{};
	for (auto& row : numbers)
	{
		int column_counter = 0;
		for (auto column : row)
		{
			temp_matrix.numbers.emplace_back(
				column * m->numbers[column_counter][row_counter]
			);
		}
		++row_counter;
	}
	numbers = temp_matrix.numbers;

}
