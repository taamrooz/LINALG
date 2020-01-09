#include "vector.h"
#include <cmath>
#include "SDL.h"

vector::vector()
{
	x = y = z = 0.0f;
}

vector::vector(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

vector& vector::operator+=(const vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vector& vector::operator-=(const vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vector& vector::operator*=(const vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vector& vector::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

vector& vector::operator/=(float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

vector vector::operator+(const vector& v) const
{
	return vector{ x + v.x, y + v.y, z + v.z };
}

vector vector::operator-(const vector& v) const
{
	return vector{ x - v.x, y - v.y, z - v.z };
}

vector vector::operator*(const vector& v) const
{
	return vector{ x * v.x, y * v.y, z * v.z };
}

vector vector::operator*(float v) const
{
	return vector{ z * v, y * v, z * v };
}

vector vector::operator/(float v) const
{
	return vector{ x / v, y / v, z / v };
}

vector vector::cross(const vector& other) const
{
	vector vec;
	vec.x = (y * other.z) - (z * other.y);
	vec.y = (z * other.x) - (x * other.z);
	vec.z = (x * other.y) - (y * other.x);
	return vec;
}

float vector::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

void vector::normalize()
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

void vector::multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void vector::render(SDL_Renderer* renderer_, int k_screen_width, int k_screen_height)
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer_, k_screen_width / 2, k_screen_height / 2, k_screen_width / 2 + x, k_screen_height / 2 + -1 * y);
}
