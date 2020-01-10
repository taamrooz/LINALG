#pragma once
#include "vec3d.h"

class camera
{
public:
	camera(float fov);
	~camera();
	camera(const camera& other) = delete;
	camera(camera&& other) = delete;
	camera& operator=(const camera& other) = delete;
	camera& operator=(camera&& other) = delete;
	void update();
private:
	
	vec3d up_;
	vec3d right_;
	vec3d direction_;
	vec3d eye_;
	vec3d lookat_;
	float fov_;
};