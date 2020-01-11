#pragma once
#include "vec3d.h"
#include <vector>

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
	object update(object& o, float move_x, float move_y, float move_z, float pitch_x, float pitch_y);
private:
	
	vec3d up_;
	vec3d right_;
	vec3d direction_;
	vec3d eye_{ 0,0,-200 };
	vec3d lookat_{ 145,88,3000 };
	float fov_;
};
