#pragma once
#include "vec3d.h"
#include <vector>

class ship;
class object;
class point;

class camera
{
public:
	camera(float fov);
	~camera();
	camera(const camera& other) = delete;
	camera(camera&& other) = delete;
	camera& operator=(const camera& other) = delete;
	camera& operator=(camera&& other) = delete;
	std::vector<object> update(ship& ship, std::vector<object>& objects);
	vec3d get_direction() const;
	vec3d get_right() const;
	vec3d get_up() const;
	void moveX(float x);
	void moveY(float y);
	void moveZ(float z);
	void pitchX(float x);
	void pitchY(float y);
	void set_lookat(vec3d v);
private:
	
	vec3d up_;
	vec3d right_;
	vec3d direction_;
	vec3d eye_{ 0,0,0 };
	vec3d lookat_{ 145,88,3000 };
	float fov_;
};
