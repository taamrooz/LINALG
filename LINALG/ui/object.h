#pragma once
#include "point.h"
#include <vector>
#include "SDL.h"
#include <unordered_map>
#include "plane.h"

class object
{
public:
	std::vector<std::shared_ptr<plane>> planes{};
	void add_plane(std::shared_ptr<plane> p);
	void add_planes(std::vector<std::shared_ptr<plane>> planes);
	void scale_from_origin(double x, double y, double z);
	void translate(double x, double y, double z);
	void scale_from_point(double scale_x, double scale_y, double scale_z);
	void rotate_origin(double degrees);
	void rotate_middle(double degrees);
	point get_middle_point();
	void link_planes();
	void move_object(vec3d& v);
};
