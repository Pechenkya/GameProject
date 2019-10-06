#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <list>
#include <stack>

#include "Weapon.h"
#include "Object.h"
#include "Vector2D.h"
#include "Pathfinding.h"

class BattleField;

class Character : public Object
{
protected:
	Weapon *using_weapon;
	int move_points{ 3 };
	int max_health;

	//Skills
	int agility{ 3 };
	int strength{ 0 };
	int additional_accuracy{ 0 };
	int stealth{ 0 };

	int loyalty_level{}; // Loyalty to main character
public:
	virtual void raise_agility(int agility_plus_count);
	virtual void set_agility(int agility_set_count);
	virtual void set_weapon(Weapon *new_weapon);
	virtual void on_attack(Character * target, BattleField * in_battle_field);
	virtual void attack(Character *target, BattleField * in_battle_field);
	virtual void get_health();
	int get_health_int();
	virtual void get_info();
	virtual void get_weapon_info();
	virtual char get_symbol() override;
	virtual void set_on_pos(int X, int Y);
	virtual void move(Object & main_characrer, int bf_size, BattleField * in_battle_field);
	virtual void move_to(int X, int Y, int bf_size, BattleField * in_battle_field);
	virtual int move_points_info();
	virtual int get_weapon_fire_rate();
	virtual int get_pos_x();
	virtual int get_pos_y();
	virtual double get_distance(int position_x, int position_y);
	virtual WeaponType get_weapon_type();
	virtual int get_weapon_distance();
	virtual Vector2D get_pos_in_battle() override;
	virtual void reset_move_points();
	Weapon* get_weapon();
	int get_agility();

	void increase_loyalty(int loyalty_difference);

	void reset_health();

	void get_killed();

	void set_life_status(bool in);
	void set_health(int health_in);
	void set_max_health(int health_in);

	int get_max_health();

	void set_loyalty(int loyalty);

	int get_loyalty();

	bool fire_line_closed(Character *target, BattleField * in_battle_field);
	void die() override;

	void queue_reverse(std::queue <Vector2D> &in_queue);

	Character(std::string name_in, Weapon* using_weapon_in, int health_in, int starting_loyalty_level);
	Character();
	~Character();
};


#endif // CHARACTER_H
