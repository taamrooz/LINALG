#pragma once
#include "point.h"
#include <vector>
#include <unordered_map>
#include "plane.h"

class object
{
public:
	object();
	std::vector<std::shared_ptr<plane>> planes{};
	void add_plane(std::shared_ptr<plane> p);
	void add_planes(std::vector<std::shared_ptr<plane>> planes);
	void scale_from_origin(float x, float y, float z);
	void translate(float x, float y, float z);
	void scale_from_point(float scale_x, float scale_y, float scale_z);
	void rotate(float degrees, vec3d position, vec3d axis);
	point get_middle_point();
	void link_planes();
	void move_object(vec3d& v);
	void set_position(vec3d v);
protected:
	vec3d position_;
private:
	void rotate_x(float degrees);
	void rotate_y(float degrees);
	void rotate_z(float degrees);
	void rotate_axis(float degrees, vec3d& axis);
};
