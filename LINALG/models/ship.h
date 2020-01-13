#pragma once
#include "object.h"
#include "bullet.h"

class ship : public object{
private:
	std::shared_ptr<point> front;
	std::shared_ptr<point> back;
	vec3d direction_;
	vec3d right_;
	vec3d up_;
	float speed_ {0.0f};
public:
	ship();
	void set_front(std::shared_ptr<point> p);
	void set_back(std::shared_ptr<point> p);
	vec3d get_direction() const;
	vec3d get_right() const;
	vec3d get_up() const;
	void roll(float degrees);
	void pitch(float degrees);
	void yaw(float degrees);
	void speed_up();
	void slow_down();
	void update();
	std::shared_ptr<bullet> shoot();
	std::shared_ptr<object> give_guide_line();
};
