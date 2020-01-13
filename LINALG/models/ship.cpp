#include "ship.h"

ship::ship()
= default;

void ship::set_front(std::shared_ptr<point> p)
{
	front = p;
}

void ship::set_back(std::shared_ptr<point> p)
{
	back = p;
}

vec3d ship::get_direction() const
{
	return direction_;
}

vec3d ship::get_right() const
{
	return right_;
}

vec3d ship::get_up() const
{
	return up_;
}

void ship::update()
{
	direction_ = front->vector - back->vector;
	direction_.normalize();
	up_ = { 0,1,0 };
	right_ = up_.cross(direction_);
	right_.normalize();
	up_ = direction_.cross(right_);
	up_.normalize();
}

