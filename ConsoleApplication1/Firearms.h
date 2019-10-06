#pragma once
#ifndef FIREARMS_H
#define FIREARMS_H

#include <string>
#include <iostream>
#include <vector>
#include <time.h>

#include "Weapon.h"
#include "Object.h"


class Firearms : public Weapon
{


	//Firearms constructor
public:
	Firearms(std::string new_w_model, int new_w_damage, int new_w_accuracy, int new_w_fire_rate, int new_w_distance);
};

#endif // FIREARMS_H
