#include "object.h"
#include "vec3d.h"
#include "standard_matrices.h"
#include "deg_helper.h"

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
	translate(0 - p_middle.vector.x, 0 - p_middle.vector.y, 0 - p_middle.vector.z);
	scale_from_origin(scale_x, scale_y, scale_z);
	translate(p_middle.vector.x, p_middle.vector.y, p_middle.vector.z);
}

void object::rotate(float degrees, vec3d& position, vec3d& axis)
{
	translate(-position.x, -position.y, -position.z);
	rotate_axis(degrees, axis);
	translate(position.x, position.y, position.z);
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

void object::rotate_axis(float degrees, vec3d& axis)
{
	//calc tau deg by z / x with inverse tan
	float tau_deg = rad_to_degree(axis.x != 0 ? atan(axis.z / axis.x) : 0);

	rotate_y(tau_deg);
	//calc cos of tau2
	float tau2_cos = sqrtf(axis.x * axis.x + axis.z * axis.z) / sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	//float tau2_sin = axis.y / sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

	float tau2_deg = rad_to_degree(acos(tau2_cos));
	rotate_z(-tau2_deg);
	rotate_x(degrees);
	rotate_z(tau2_deg);
	rotate_y(-tau_deg);
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
