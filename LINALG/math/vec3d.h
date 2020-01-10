#pragma once

class vec3d
{
public:
	vec3d();
	vec3d(float, float, float);
	vec3d& operator+=(const vec3d& v);
	vec3d& operator-=(const vec3d& v);
	vec3d& operator*=(const vec3d& v);
	vec3d& operator*=(float v);
	vec3d& operator/=(float v);
	vec3d operator+(const vec3d& v) const;
	vec3d operator-(const vec3d& v) const;
	vec3d operator*(const vec3d& v) const;
	vec3d operator*(float v) const;
	vec3d operator/(float v) const;
	vec3d cross(const vec3d& other) const;
	float in(const vec3d& other) const;
	float length() const;
	void normalize();
	void multiply(float scalar);
	float x, y, z;
};
