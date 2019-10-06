#pragma once
#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Weapon.h"
#include "Object.h"


class MeleeWeapon : public Weapon
{


	//Melee weapon constructor
public:
	MeleeWeapon(std::string new_w_model, int new_w_damage, int new_w_fire_rate);
};


#endif // MELEEWEAPON_H
