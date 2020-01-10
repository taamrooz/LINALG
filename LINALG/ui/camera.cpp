#include "camera.h"
#include "matrix.h"

constexpr auto PI = 3.14159265358979323846;
constexpr auto PI_F(static_cast<float>(PI));

inline float deg_to_radian(float degrees) { return degrees * 180.f / PI_F; }

camera::camera(float fov) : fov_(90)
{
}

camera::~camera()
= default;

void camera::update()
{
	direction_ = eye_ - lookat_;
	direction_.normalize();
	up_ = { 0,1,0 };
	right_ = up_.cross(direction_);
	right_.normalize();
	up_ = direction_.cross(right_);
	up_.normalize();
	auto m = matrix{ 4,4 };
	m.numbers[0][0] = right_.x;     m.numbers[0][1] = right_.y;     m.numbers[0][2] = right_.z;     m.numbers[0][3] = -right_.in(eye_);
	m.numbers[1][0] = up_.x;        m.numbers[1][1] = up_.y;        m.numbers[1][2] = up_.z;        m.numbers[1][3] = -up_.in(eye_);
	m.numbers[2][0] = direction_.x; m.numbers[2][1] = direction_.y; m.numbers[2][2] = direction_.z; m.numbers[2][3] = -direction_.in(eye_);
	m.numbers[3][0] = 0;            m.numbers[3][1] = 0;			m.numbers[3][2] = 0;			m.numbers[3][3] = 1;

	
}
