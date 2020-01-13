#include "camera.h"
#include "matrix.h"
#include "object.h"
#include "point.h"
#include "../models/ship.h"
#include "deg_helper.h"

camera::camera(float fov) : fov_(fov)
{
}

camera::~camera()
= default;

std::vector<object> camera::update(ship& ship, std::vector<object>& objects)
{
	lookat_ = ship.get_middle_point().vector;
	direction_ = eye_ - lookat_;
	direction_.normalize();
	up_ = { 0,1,0 };
	right_ = up_.cross(direction_);
	right_.normalize();
	up_ = direction_.cross(right_);
	up_.normalize();
	auto cam_m = matrix{ 4,4 };
	cam_m.numbers[0][0] = right_.x;     cam_m.numbers[0][1] = right_.y;     cam_m.numbers[0][2] = right_.z;     cam_m.numbers[0][3] = -right_.in(eye_);
	cam_m.numbers[1][0] = up_.x;        cam_m.numbers[1][1] = up_.y;        cam_m.numbers[1][2] = up_.z;        cam_m.numbers[1][3] = -up_.in(eye_);
	cam_m.numbers[2][0] = direction_.x; cam_m.numbers[2][1] = direction_.y; cam_m.numbers[2][2] = direction_.z; cam_m.numbers[2][3] = -direction_.in(eye_);
	cam_m.numbers[3][0] = 0;            cam_m.numbers[3][1] = 0;			cam_m.numbers[3][2] = 0;			cam_m.numbers[3][3] = 1;

	float near = 0.1;
	float far = 5;
	float scale = near * tanf(deg_to_radian(fov_) * 0.5f);

	auto per_m = matrix{ 4,4 };

	per_m.numbers[0][0] = scale; per_m.numbers[0][1] = 0;     per_m.numbers[0][2] = 0;							  per_m.numbers[0][3] = 0;
	per_m.numbers[1][0] = 0;     per_m.numbers[1][1] = scale; per_m.numbers[1][2] = 0;							  per_m.numbers[1][3] = 0;
	per_m.numbers[2][0] = 0;     per_m.numbers[2][1] = 0;     per_m.numbers[2][2] = -far / (far - near);		  per_m.numbers[2][3] = -1;
	per_m.numbers[3][0] = 0;	 per_m.numbers[3][1] = 0;	  per_m.numbers[3][2] = (-far * near) / (far - near); per_m.numbers[3][3] = 0;
	
	std::vector<object> res_objs;
	for (auto& o : objects) {
		object res_o{};
		for (const auto& pl : o.planes)
		{
			std::vector<std::shared_ptr<point>> res_p;
			for (auto& p : pl->points)
			{
				auto r = cam_m.multiply_vector(p->vector);
				r = r.multiply_matrix(per_m);
				point new_p{ r.numbers[0][0], r.numbers[1][0], r.numbers[2][0], r.numbers[3][0] };
				auto screenSizeX = far / tan(fov_ / 2) * 2;
				auto screenSizeY = screenSizeX;
				new_p.vector.x = (screenSizeX / 2) + (new_p.vector.x + 1) / new_p.w * screenSizeX * 0.5 + 400;
				new_p.vector.y = (screenSizeY / 2) + (new_p.vector.y + 1) / new_p.w * screenSizeY * 0.5 + 300;
				//new_p.vector.z = -new_p.vector.z;
				res_p.push_back(std::make_shared<point>(new_p));
			}
			res_o.add_plane(std::make_shared<plane>(res_p));
		}
		res_o.link_planes();
		res_objs.push_back(res_o);
	}
	return res_objs;
}

vec3d camera::get_direction() const
{
	return direction_;
}

vec3d camera::get_right() const
{
	return right_;
}

vec3d camera::get_up() const
{
	return up_;
}

void camera::moveX(float x)
{
	eye_.x += x;
}

void camera::moveY(float y)
{
	eye_.y += y;
}

void camera::moveZ(float z)
{
	eye_.z += z;
}

void camera::pitchX(float x)
{
	lookat_.x += x;
}

void camera::pitchY(float y)
{
	lookat_.y += y;
}





