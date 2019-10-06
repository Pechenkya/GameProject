#pragma once
#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Character.h"
#include "Weapon.h"
#include "Enemy.h"
#include "MeleeWeapon.h"

class MainCharacter : public Character
{
private:
	int syringes{ 0 };

	int leveling_points{ 5 };

	Weapon * primary_weapon{ nullptr };
	Weapon * secondary_weapon{ nullptr };

	int karma{ 0 }; //Karma level
public:
	void add_syringes(int syringes_to_add);
	void healup();
	char get_symbol() override;
	void get_info() override;
	void reset_move_points() override;
	void get_weapon_info() override;

	void increase_lvl();
	void increase_lvl(int lvl_points);

	void increase_skills();

	void increase_agility(int lvl_points);
	void increase_strength(int lvl_points);
	void increase_accuracy(int lvl_points);
	void increase_stealth(int lvl_points);

	void cheats(std::string code);

	void increase_karma(int karma_difference);
	int get_karma();

	void move(int bf_size, BattleField * in_battle_field);
	void move_to(int X, int Y, int bf_size, BattleField * in_battle_field) override;

	void on_attack(Character * target, BattleField * in_battle_field) override;
	void attack(std::vector <Enemy> &enemies, BattleField * in_battle_field);

	void set_weapon(Weapon *new_weapon) override;

	void die() override;

	void swap_weapon();

	void leave_weapon();

	void set_health(int health_in);
	void set_lvl_points(int lvl_points);
	void set_strength(int lvl_points);
	void set_accuracy(int lvl_points);
	void set_stealth(int lvl_points);
	void set_karma(int karma_level);

	int get_strength();
	int get_additiona_accuracy();
	int get_stealth();
	int get_lvl_points();
	int get_syringes_count();

	// Main Character constructor
	MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon);
	MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon, int input_agility);
	MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon, MeleeWeapon *std_secondary_weapon);
	MainCharacter(std::string input_name, int input_hp, Weapon * std_using_weapon, MeleeWeapon * std_secondary_weapon, int input_agility);
	MainCharacter();
};


#endif // MAINCHARACTER_H
