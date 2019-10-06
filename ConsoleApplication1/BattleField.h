#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <list>
#include <queue>
#include <stack>
#include "windows.h"

#include "Object.h"
#include "Character.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Vector2D.h"
#include "Weapon.h"
#include "Firearms.h"
#include "MeleeWeapon.h"
#include "Pathfinding.h"
#include "Obstacle.h"
#include "BattleMode.h"

class BattleField
{
protected:

	size_t battle_field_size{ 9 };
	std::vector <std::vector <char>> visual_bf;
	std::string input{};
	char temp_symbol{};
	bool main_character_surrendered{ false };

	//Battlefield methods
	void initialize_battle(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies, std::vector <Obstacle> &obstacles);
	virtual void set_objects_on_positions(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void build_battle_field_scheme();
	void fill_info_lists(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies, std::vector <Obstacle> &obstacles);
	void visualise_status(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void battle_starting(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void main_battle_loop(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void main_character_turn(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void visualise_user_choosements(MainCharacter & main_character);
	char user_input_in_UI(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void process_user_selecion(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies, char us_input);
	void enemy_turn(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);
	void reset_enemies_move_points(std::vector <Enemy> &group_of_enemies);

	//Clearing methods
	void clear();


public:
	//Out visual methods
	void visualise_grid();
	void visualise_grid(std::vector<std::vector<char>> bf_copy);
	std::vector <std::vector <char>> get_grid_copy();

	//Checking status
	bool return_enemy_life_status_info(std::vector <Enemy> &group_of_enemies);
	bool check_node(Vector2D pos);
	bool battle_start_status(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies);

	//Location info
	static std::list <Object*> Obstacles;		//For Main Character
	static std::list <Object*> Objects;			//For Enemies

	//Pathfinding component
	static PathfindingComponent path_finding;
	static GridQueryComponent grid_query_component;

	void new_battle(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies, std::vector <Obstacle> &obstacles, bool & surrender_status);

	//Refresh methods
	void refresh();

	//Battlefield destructor
	~BattleField();
};

