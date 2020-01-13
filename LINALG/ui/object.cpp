#include "object.h"
#include "vec3d.h"
#include "standard_matrices.h"

void object::add_plane(std::shared_ptr<plane> p)
{
	planes.emplace_back(p);
}

void object::add_planes(std::vector<std::shared_ptr<plane>> ps)
{
	for (auto& p : ps)
	{
		planes.emplace_back(p);
	}
}

void object::scale_from_origin(double x, double y, double z)
{
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			auto m = matrix{};
			m.numbers.emplace_back(std::vector<float>{point->vector.x});
			m.numbers.emplace_back(std::vector<float>{point->vector.y});
			m.numbers.emplace_back(std::vector<float>{point->vector.z});
			m.numbers.emplace_back(std::vector<float>{1});
			auto s = scaling_matrix_3d(x, y, z);
			s = s.multiply_matrix(m);
			point->vector.x = m.numbers[0][0];
			point->vector.y = m.numbers[1][0];
			point->vector.z = m.numbers[2][0];
		}
	}
}

void object::translate(double x, double y, double z)
{
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			auto m = matrix{};
			m.numbers.emplace_back(std::vector<float>{point->vector.x});
			m.numbers.emplace_back(std::vector<float>{point->vector.y});
			m.numbers.emplace_back(std::vector<float>{point->vector.z});
			m.numbers.emplace_back(std::vector<float>{1});
			auto t = translation_matrix_3d(x, y, z);
			t.multiply_matrix(m);
			point->vector.x = t.numbers[0][0];
			point->vector.y = t.numbers[1][0];
			point->vector.z = t.numbers[2][0];
		}
	}
}

void object::scale_from_point(double scale_x, double scale_y, double scale_z)
{
	auto p_middle = get_middle_point();
	translate(0.0f - p_middle.vector.x, 0.0f - p_middle.vector.y, 0.0f - p_middle.vector.z);
	scale_from_origin(scale_x, scale_y, scale_z);
	translate(p_middle.vector.x, p_middle.vector.y, p_middle.vector.z);
}

//void object::rotate_origin(double degrees)
//{
//	for (auto& point : points)
//	{
//		auto v = vector{
//		point->vector.x,
//		point->vector.y,
//		point->vector.z
//		};
//		auto m = rotation_matrix_2d(degrees);
//		m.multiply_vector(&v);
//		point->vector.x = m.numbers[0][0];
//		point->vector.y = m.numbers[1][0];
//		point->vector.z = m.numbers[2][0];
//	}
//}
//
//void object::rotate_middle(double degrees)
//{
//	auto p_middle = get_middle_point();
//	translate(0 - p_middle.x, 0 - p_middle.y);
//	for (auto& point : points)
//	{
//		auto v = vector{
//		point->x,
//		point->y,
//		point->z
//		};
//		auto m = rotation_matrix_2d(degrees);
//		m.multiply_vector(&v);
//		point->x = m.numbers[0][0];
//		point->y = m.numbers[1][0];
//	}
//	translate(p_middle.x, p_middle.y);
//}

point object::get_middle_point()
{
	float total_x = 0;
	float total_y = 0;
	float total_z = 0;
	float total = 0;
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			total_x += point->vector.x;
			total_y += point->vector.y;
			total_z += point->vector.z;
			total++;
		}
	}
	total_x /= total;
	total_y /= total;
	total_z /= total;
	return {
		{total_x,
		total_y,
		total_z}
	};
}

void object::link_planes()
{
	for (auto& plane : planes)
	{
		plane->link_points();
	}
}

void object::move_object(vec3d& v)
{
	for (auto& p : planes)
	{
		p->move_object(v);
	}
}
