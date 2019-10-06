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
#include "BattleField.h"

//Modes
#include "BattleMode.h"
#include "StoryMode.h"

class MainMenu
{
private:

	std::string battle_field_type{"Common"};
	std::string main_character_name{"Main Character"};
	std::string enemy_name{ "Enemy" };
	std::vector <Obstacle> using_obstacle_preset;
	std::string using_obstacle_preset_name{"Wasteland"};
	int obstacle_preset_num = 0;
	std::vector <std::string> obstacle_preset_names;
	char user_input_key{};
public:
	static std::vector <std::vector <Obstacle>> obstacle_presets;
	static std::vector <Obstacle> special_obstacle_preset;

	MainCharacter *main_character = nullptr;
	void user_menu();
	void welcome_screen();
	void enter_battle_mode();
	void options();
	void battle_mode_options();
	void story_mode_options();
	void change_main_character_name();
	void change_enemy_name();
	void change_battle_field_type();
	void change_obstacle_preset();
	void create_obstacle_presets();
	void enter_story_mode();
	static void show_out_message(std::string message);
};

