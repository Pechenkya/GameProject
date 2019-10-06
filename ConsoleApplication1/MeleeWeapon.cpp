#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(std::string new_w_model, int new_w_damage, int new_w_fire_rate)
{
	model = new_w_model;
	damage = new_w_damage;
	accuracy = 100;
	fire_rate = new_w_fire_rate;
	wtype = WeaponType::Melee;
	distance = 1.5;
}
