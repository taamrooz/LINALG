#include "cube.h"
#include "bullet.h"
#include <iostream>

void cube::update()
{
	if(size < 90)
	{
		grow = true;
	}
	if(size > 110)
	{
		grow = false;
	}
	float scale = 0.99;
	if (grow)
	{
		scale = 1.01;
	}

	size *= scale;
	scale_from_point(scale, scale, scale);
}

bool cube::collision_check(object& b)
{
	auto my_bb = get_aabb();
	for (auto& plane : b.planes)
	{
		for (auto& point : plane->points)
		{
			if(point->vector.x > my_bb.min_values.x && point->vector.x < my_bb.max_values.x
				&& point->vector.y > my_bb.min_values.y && point->vector.y < my_bb.max_values.y
				&& point->vector.z > my_bb.min_values.z && point->vector.z < my_bb.max_values.z)
			{
				return true;
			}
		}
	}
	return false;
}
