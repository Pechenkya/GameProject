#include "Obstacle.h"

char Obstacle::get_symbol()
{
	return 'W';
}

Obstacle::Obstacle(Vector2D pos)
{
	this->pos_in_battle = pos;
	this->object_type = "Obstacle";
}

Vector2D Obstacle::get_pos_in_battle()
{
	return pos_in_battle;
}
