#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>


class Object;

enum WeaponType
{
	Melee,
	Range
};


class Weapon
{
protected:
	int damage;         //Weapon damage
	int accuracy;       //Weapon accuracy (1-100)
	int fire_rate;      //Weapon fire rate (1-10)
	double distance;       //Comfortable distance to shoot
	std::string model;       //Weapon model
	WeaponType wtype;       //Weapon type

// Weapon methods
public:
	virtual void use_weapon(Object *choosen_person, int distance_bonus, std::string character_name, bool & miss);
	virtual void get_weapon_info();
	virtual int get_distance();
	virtual int get_fire_rate();
	virtual int get_damage();
	std::string get_model();
	WeaponType get_weapon_type();
};


#endif // WEAPON_H
