#include "object.h"
#include "vec3d.h"
#include "standard_matrices.h"
#include "deg_helper.h"
#include <functional>

object::object()
{
	position_ = get_middle_point().vector;
}

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

void object::scale_from_origin(float x, float y, float z)
{
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			auto v = vec3d{
			point->vector.x,
			point->vector.y,
			point->vector.z
			};
			auto m = scaling_matrix_3d(x, y, z);
			auto res = m.multiply_vector(v);
			point->vector.x = res[0][0];
			point->vector.y = res[1][0];
			point->vector.z = res[2][0];
		}
	}
}

void object::translate(float x, float y, float z)
{
	std::vector<std::shared_ptr<point>> visited_points{};
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			if(std::find(visited_points.begin(), visited_points.end(), point) != visited_points.end())
			{
				continue;
			}
			visited_points.emplace_back(point);
			auto m = matrix{};
			m.numbers.emplace_back(std::vector<float>{point->vector.x});
			m.numbers.emplace_back(std::vector<float>{point->vector.y});
			m.numbers.emplace_back(std::vector<float>{point->vector.z});
			m.numbers.emplace_back(std::vector<float>{1});
			auto t = translation_matrix_3d(x, y, z);
			auto res = t * m;
			point->vector.x = res[0][0];
			point->vector.y = res[1][0];
			point->vector.z = res[2][0];
		}
	}
}

void object::scale_from_point(float scale_x, float scale_y, float scale_z)
{
	auto p_middle = get_middle_point();
	translate(0.0f - p_middle.vector.x, 0.0f - p_middle.vector.y, 0.0f - p_middle.vector.z);
	scale_from_origin(scale_x, scale_y, scale_z);
	translate(p_middle.vector.x, p_middle.vector.y, p_middle.vector.z);
}

void object::rotate(float degrees, vec3d position, vec3d axis)
{
	translate(-position.x, -position.y, -position.z);
	rotate_axis(degrees, axis);
	translate(position.x, position.y, position.z);
}

void object::rotate_axis(float degrees, vec3d& axis)
{
	//calc tau deg by z / x with inverse tan
	float tau_deg = rad_to_degree(axis.x != 0 ? atanf(axis.z / axis.x) : 0);
	rotate_y(tau_deg);
	//calc cos of tau2
	float tau2_cos = sqrtf(axis.x * axis.x + axis.z * axis.z) / sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

	float tau2_deg = rad_to_degree(acos(tau2_cos));
	rotate_z(-tau2_deg);
	rotate_x(degrees);
	rotate_z(tau2_deg);
	rotate_y(-tau_deg);
}

void object::rotate_x(float degrees)
{
	auto rad = deg_to_radian(degrees);
	auto rot = rotation_matrix_3d_x(rad);
	for(auto& plane: planes)
	{
		for(auto& point: plane->points)
		{
			auto res_v = rot.multiply_vector(point->vector);
			point->vector.x = res_v[0][0];
			point->vector.y = res_v[1][0];
			point->vector.z = res_v[2][0];
		}
	}
}

void object::rotate_y(float degrees)
{
	auto rad = deg_to_radian(degrees);
	auto rot = rotation_matrix_3d_y(rad);
	for (auto& plane : planes)
	{
		for(auto& point: plane->points)
		{
			auto res_v = rot.multiply_vector(point->vector);
			point->vector.x = res_v[0][0];
			point->vector.y = res_v[1][0];
			point->vector.z = res_v[2][0];
		}
	}
}

void object::rotate_z(float degrees)
{
	auto rad = deg_to_radian(degrees);
	auto rot = rotation_matrix_3d_z(rad);
	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			auto res_v = rot.multiply_vector(point->vector);
			point->vector.x = res_v[0][0];
			point->vector.y = res_v[1][0];
			point->vector.z = res_v[2][0];
		}
	}
}



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

void object::set_position(vec3d v)
{
	position_ = v;
}

aabb object::get_aabb()
{
	float min_x = FLT_MAX;
	float min_y = FLT_MAX;
	float min_z = FLT_MAX;
	float max_x = FLT_MIN;
	float max_y = FLT_MIN;
	float max_z = FLT_MIN;

	for (auto& plane : planes)
	{
		for (auto& point : plane->points)
		{
			if (point->vector.x < min_x) { min_x = point->vector.x; }
			if (point->vector.y < min_y) { min_y = point->vector.y; }
			if (point->vector.z < min_z) { min_z = point->vector.z; }
			if (point->vector.x > max_x) { max_x = point->vector.x; }
			if (point->vector.y > max_y) { max_y = point->vector.y; }
			if (point->vector.z > max_z) { max_z = point->vector.z; }
		}
	}

	aabb aa_bb{};
	aa_bb.min_values = {min_x, min_y, min_z};
	aa_bb.max_values = { max_x, max_y, max_z };
	return aa_bb;
}
