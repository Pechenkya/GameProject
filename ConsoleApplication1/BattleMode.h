#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "windows.h"
#include <list>
#include <queue>

//Objects
#include "Object.h"
#include "Character.h"
#include "MainCharacter.h"
#include "Enemy.h"

//Weapon
#include "Weapon.h"
#include "Firearms.h"
#include "MeleeWeapon.h"

//Assising classes
#include "Vector2D.h"

//Locations
#include "Battlefield.h"

class BattleMode
{
	MainCharacter main_character;
	int group_of_enemies_size;
	bool surrender_status {false};
	std::string battle_mode_type{};
	std::string enemy_name;
	std::vector <Enemy> group_of_enemies;
	std::vector <Obstacle> obstacle_preset;
public:
	
	static std::vector <Weapon> weapon_list;

	void battle_mode();
	void set_weapon_on_character();
	void create_enemies();
	static void create_weapons();
	void battle_mode_results();
	BattleMode(MainCharacter main_character_in, int group_of_enemies_size_in, std::string enemy_name_in, std::vector <Obstacle> obstacle_preset_in, std::string battle_mode_type_in);
};

