#include "Object.h"
#include "windows.h"

void Object::take_damage(int taken_damage)
{
	if (this->alive)
	{
		health = health - taken_damage;
		if (health <= 0)
		{
			this->health = 0;
			die();
		}
	}
};

bool Object::get_alive_status()
{
	return alive;
}

void Object::die()
{
	this->alive = false;
	std::cout << this->name << " died" << std::endl << std::endl;
	pos_in_battle = Vector2D(1000, 1000);
};

void Object::show_out_message(std::string message)
{
	for (auto c : message)
	{
		std::cout << c;
		Sleep(25);
	}
	std::cout << std::endl << std::endl;
}

//virtual Object::Vector2D get_pos_in_battle() = 0;

Object::~Object()
{
}

