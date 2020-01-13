#pragma once
constexpr auto PI = 3.14159265358979323846;
constexpr auto PI_F(static_cast<float>(PI));

inline float deg_to_radian(float degrees) { return degrees * PI_F / 180.f; }
inline float rad_to_degree(float radian) { return radian / PI_F * 180.f; }