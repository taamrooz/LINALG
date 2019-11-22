#include "object.h"
#include "standard_matrices.h"

void object::add_point(std::shared_ptr<point> p)
{
	points.emplace_back(p);
}

void object::render(SDL_Renderer* renderer_)
{
	for (const auto& point : points)
	{
		point->render(renderer_);
		for (auto connection : point->connections)
		{
			SDL_RenderDrawLine(renderer_, connection->get_render_x(), connection->get_render_y(), point->get_render_x(), point->get_render_y());
		}
	}
}

void object::scale_from_origin(double x, double y)
{
	for (auto& point : points)
	{
		auto v = vector{
		point->x,
		point->y
		};
		auto m = scaling_matrix(x, y);
		m.multiply_vector(&v);
		point->x = m.numbers[0][0];
		point->y = m.numbers[1][0];
	}	
}

void object::translate(double x, double y)
{
	for (auto& point : points)
	{
		auto m = matrix{};
		m.numbers.emplace_back(std::vector<float>{point->x});
		m.numbers.emplace_back(std::vector<float>{point->y});
		m.numbers.emplace_back(std::vector<float>{1});
		auto t = translation_matrix(x, y);
		t.multiply_matrix(&m);
		point->x = t.numbers[0][0];
		point->y = t.numbers[1][0];
	}
}

void object::scale_from_point(double scale_x, double scale_y)
{
	auto p_middle = get_middle_point();
	translate(0 - p_middle.x, 0 - p_middle.y);
	scale_from_origin(scale_x, scale_y);
	translate(p_middle.x, p_middle.y);
}

void object::rotate_origin(double degrees)
{
	for (auto& point : points)
	{
		auto v = vector{
		point->x,
		point->y
		};
		auto m = rotation_matrix(degrees);
		m.multiply_vector(&v);
		point->x = m.numbers[0][0];
		point->y = m.numbers[1][0];
	}
}

void object::rotate_middle(double degrees)
{
	auto p_middle = get_middle_point();
	translate(0 - p_middle.x, 0 - p_middle.y);
	for (auto& point : points)
	{
		auto v = vector{
		point->x,
		point->y
		};
		auto m = rotation_matrix(degrees);
		m.multiply_vector(&v);
		point->x = m.numbers[0][0];
		point->y = m.numbers[1][0];
	}
	translate(p_middle.x, p_middle.y);
}

point object::get_middle_point()
{
	float total_x = 0;
	float total_y = 0;
	for (auto& point : points)
	{
		total_x += point->x;
		total_y += point->y;
	}
	total_x /= points.size();
	total_y /= points.size();
	return {
		total_x,
		total_y,
		0,0
	};
}
