#pragma once
#include "object.h"

class ship : public object{
public:
	ship();
	void move_up();
	void move_down();
	void move_forward();
	void move_left();
	void move_right();
	void move_back();
};
