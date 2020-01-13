#include "bullet.h"
#include "vec3d.h"
#include <memory>
#include "point.h"

void bullet::set_front(std::shared_ptr<point> p)
{
	front = p;
}

void bullet::set_back(std::shared_ptr<point> p)
{
	back = p;
}

vec3d bullet::get_direction() const
{
	return direction_;
}

vec3d bullet::get_right() const
{
	return right_;
}

vec3d bullet::get_up() const
{
	return up_;
}

void bullet::set_speed(float speed)
{
	speed_ = speed;
}

void bullet::update()
{
	direction_ = front->vector - back->vector;
	direction_.normalize();
	up_ = { 0,1,0 };
	right_ = up_.cross(direction_);
	right_.normalize();
	up_ = direction_.cross(right_);
	up_.normalize();

	auto movement = direction_ * speed_;
	move_object(movement);
}
