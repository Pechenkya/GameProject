#include "Firearms.h"
#include "Weapon.h"

Firearms::Firearms(std::string new_w_model, int new_w_damage, int new_w_accuracy, int new_w_fire_rate, int new_w_distance)
{
	{
		model = new_w_model;
		damage = new_w_damage;
		accuracy = new_w_accuracy;
		fire_rate = new_w_fire_rate;
		distance = new_w_distance;
		wtype = WeaponType::Range;
	}
}
