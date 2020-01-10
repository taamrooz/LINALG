#include "vec3d.h"
#include <cmath>

vec3d::vec3d()
{
	x = y = z = 0.0f;
}

vec3d::vec3d(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

vec3d& vec3d::operator+=(const vec3d& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3d& vec3d::operator-=(const vec3d& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3d& vec3d::operator*=(const vec3d& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec3d& vec3d::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

vec3d& vec3d::operator/=(float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

vec3d vec3d::operator+(const vec3d& v) const
{
	return vec3d{ x + v.x, y + v.y, z + v.z };
}

vec3d vec3d::operator-(const vec3d& v) const
{
	return vec3d{ x - v.x, y - v.y, z - v.z };
}

vec3d vec3d::operator*(const vec3d& v) const
{
	return vec3d{ x * v.x, y * v.y, z * v.z };
}

vec3d vec3d::operator*(float v) const
{
	return vec3d{ z * v, y * v, z * v };
}

vec3d vec3d::operator/(float v) const
{
	return vec3d{ x / v, y / v, z / v };
}

vec3d vec3d::cross(const vec3d& other) const
{
	vec3d vec;
	vec.x = (y * other.z) - (z * other.y);
	vec.y = (z * other.x) - (x * other.z);
	vec.z = (x * other.y) - (y * other.x);
	return vec;
}

float vec3d::in(const vec3d& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float vec3d::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

void vec3d::normalize()
{
	auto length = this->length();
	if (length != 0.0f)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	else
	{
		x = y = 0.0f; z = 1.0f;
	}
}

void vec3d::multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
