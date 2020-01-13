#include "ship.h"
#include "bullet.h"

ship::ship()
{
}

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



void ship::speed_up()
{
	if(speed_ < 3.0f)
	{
		speed_ += 0.1f;
	}
}

void ship::slow_down()
{
	if (speed_ > 0)
	{
		speed_ -= 0.1f;
	}
	if (speed_ < 0)
		speed_ = 0;
}

void ship::roll(float degrees)
{
	rotate(degrees, get_middle_point().vector, direction_);
}

void ship::pitch(float degrees)
{
	rotate(degrees, get_middle_point().vector, right_);
}

void ship::yaw(float degrees)
{
	rotate(degrees, get_middle_point().vector, up_);
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

	auto movement = direction_ * speed_ * -1;
	move_object(movement);
}

std::shared_ptr<bullet> ship::shoot()
{
	bullet b{};
	auto dir = get_direction();
	dir *= 10;
	auto front = std::make_shared<point>(point{ get_middle_point().vector -  dir });
	auto back = std::make_shared<point>(point{ get_middle_point().vector });
	b.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
			front,
			back,
	})});
	b.set_front(front);
	b.set_back(back);
	b.link_planes();
	b.set_speed(5 + speed_);
	return std::make_shared<bullet>(b);
}

std::shared_ptr<object> ship::give_guide_line()
{
	vec3d guide_line_end = direction_;
	guide_line_end *= 1000;
	object o {};
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
			std::make_shared<point>(point{ get_middle_point().vector - guide_line_end }),
			std::make_shared<point>(point{ get_middle_point().vector })
	}) });
	return std::make_shared<object>(o);
}

