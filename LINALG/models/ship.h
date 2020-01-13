#pragma once
#include "object.h"

class ship : public object{
private:
	std::shared_ptr<point> front;
	std::shared_ptr<point> back;
	vec3d direction_;
	vec3d right_;
	vec3d up_;
public:
	ship();
	void set_front(std::shared_ptr<point> p);
	void set_back(std::shared_ptr<point> p);
	vec3d get_direction() const;
	vec3d get_right() const;
	vec3d get_up() const;
	void update();	
};
