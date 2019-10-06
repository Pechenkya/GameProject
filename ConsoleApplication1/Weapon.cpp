#include "Weapon.h"
#include "Object.h"


void Weapon::use_weapon(Object * choosen_person, int distance_bonus, std::string character_name, bool & miss)
{
	int shot_accuracy = accuracy + distance_bonus;
	if ((rand() % 1000) < shot_accuracy * 10)
	{
		choosen_person->take_damage(damage);
		miss = false;
	}
	else
		miss = true;
}

void Weapon::get_weapon_info()
{
	std::cout << model << " (" << wtype << "): damage - " << damage << ", accuracy - " << accuracy << ", fire rate - " << fire_rate << ", distance - " << distance << "." << std::endl;
}

int Weapon::get_distance()
{
	return this->distance;
}

int Weapon::get_fire_rate()
{
	return this->fire_rate;
}

int Weapon::get_damage()
{
	return damage;
}

std::string Weapon::get_model()
{
	return model;
}

WeaponType Weapon::get_weapon_type()
{
	return wtype;
}