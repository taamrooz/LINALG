#pragma once
#include "object.h"

class cube : public object
{
public:
	void update();
	bool collision_check(object& b);
private:
	bool grow{ false };
	float size{ 100 };
};
