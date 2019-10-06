#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Weapon.h"
#include "Vector2D.h"
class Object
{
protected:
	int health;
	bool alive;
	Vector2D pos_in_battle;
public:
	std::string name;
	std::string object_type;

	// Object methods
	virtual void take_damage(int damage_taken);
	virtual void die();
	virtual bool get_alive_status();
	virtual char get_symbol() = 0;
	virtual Vector2D get_pos_in_battle() = 0;
	static void show_out_message(std::string message);

	// Object destructor

public:
	~Object();
};

#endif // OBJECT_H

