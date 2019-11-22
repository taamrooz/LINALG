#pragma once

class renderable
{
public:
	int x;
	int y;
	int screen_width;
	int screen_height;
	int get_render_x() const
	{
		return screen_width / 2 + x;
	};
	int get_render_y() const
	{
		return screen_height / 2 + -1 * y;
	};
	renderable(int x, int y, int screen_width, int screen_height):
	x(x), y(y), screen_width(screen_width), screen_height(screen_height)
	{}
	
};