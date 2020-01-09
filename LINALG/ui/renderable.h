#pragma once

class renderable
{
public:
	float x;
	float y;
	float z;
	int screen_width;
	int screen_height;
	float get_render_x() const
	{
		return screen_width / 2 + x;
	};
	float get_render_y() const
	{
		return screen_height / 2 + -1 * y;
	};
	renderable(float x, float y, float z, int screen_width, int screen_height):
	x(x), y(y), z(z), screen_width(screen_width), screen_height(screen_height)
	{}
	
};