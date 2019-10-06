#pragma once
#include "Object.h"

class Obstacle : public Object
{
public:
	char get_symbol() override;
	Obstacle(Vector2D pos);
	Vector2D get_pos_in_battle() override;
};

