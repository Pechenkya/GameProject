#include "Enemy.h"
#include "Weapon.h"

char Enemy::get_symbol()
{
	return this->name[name.size() - 1];
}

Enemy::Enemy(Character character)
{
	alive = character.get_alive_status();
	name = character.name + " | " + character.name[0];
	health = character.get_health_int();
	using_weapon = character.get_weapon();
	agility = move_points = character.get_agility();
	this->object_type = "Enemy";
}

Enemy::Enemy(std::string input_name, int input_hp, Weapon *new_using_weapon)
{
	alive = true;
	name = input_name;
	health = input_hp;
	using_weapon = new_using_weapon;
	move_points = 3;
	agility = 3;
	this->object_type = "Enemy";
}

Enemy::Enemy(std::string input_name, int input_hp, Weapon *std_using_weapon, int input_agility)
{
	alive = true;
	name = input_name;
	health = input_hp;
	using_weapon = std_using_weapon;
	move_points = input_agility;
	agility = input_agility;
	this->object_type = "Enemy";
}

Enemy::Enemy()
{
	alive = true;
	name = "NoName";
	health = 100;
	using_weapon = nullptr;
	this->object_type = "Enemy";
}


