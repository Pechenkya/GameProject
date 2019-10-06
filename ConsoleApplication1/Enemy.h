#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Character.h"
#include "Weapon.h"

class Enemy : public Character
{
public:

	//Enemy methods
	char get_symbol() override;
	// Enemy constructor
	Enemy(Character character);
	Enemy(std::string input_name, int input_hp, Weapon *new_using_weapon);
	Enemy(std::string input_name, int input_hp, Weapon * std_using_weapon, int input_agility);
	Enemy();
};


#endif // ENEMY_H
