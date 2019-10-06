#include "MainCharacter.h"
#include "BattleField.h"


void MainCharacter::add_syringes(int syringes_to_add)
{
	syringes += syringes_to_add;
}

void MainCharacter::healup()
{
	if (syringes > 0)
	{
		this->move_points--;
		syringes--;
		health += 50;
		if (health > max_health)
		{
			health = max_health;
		}
		std::cout << name << " healed up" << std::endl << std::endl;
	}
	else std::cout << "You need more syringes!" << std::endl << std::endl;
}

char MainCharacter::get_symbol()
{
	return this->name[0];
}

void MainCharacter::get_info()
{
	std::cout << this->name << ": " << this->health << "HP. ";
	this->get_weapon_info();
	std::cout << std::endl << "Move points: " << move_points_info() << std::endl;
	std::cout << "Syringes: " << syringes << std::endl;
}

void MainCharacter::reset_move_points()
{
	move_points = agility;
}

void MainCharacter::get_weapon_info()
{

	std::cout << " Using weapon: ";
	using_weapon->get_weapon_info();

	if (using_weapon == primary_weapon)
	{
		if (secondary_weapon != nullptr)
		{
			std::cout << std::endl << "Another Weapon: ";
			secondary_weapon->get_weapon_info();
		}
	}
	else if (using_weapon == secondary_weapon)
	{
		if (primary_weapon != nullptr)
		{
			std::cout << std::endl << "Another Weapon: ";
			primary_weapon->get_weapon_info();
		}
	}

}



void MainCharacter::increase_lvl()
{
	leveling_points++;
	system("CLS");
	std::cout << "Level increased!" << std::endl;
	std::cout << "You got 1 more leveling point!" << std::endl;
	Sleep(1000);
}

void MainCharacter::increase_lvl(int lvl_points)
{
	leveling_points += lvl_points;
	system("CLS");
	std::cout << "Level increased!" << std::endl;
	std::cout << "You got " << lvl_points << " more leveling points!" << std::endl;
	Sleep(1000);
}

void MainCharacter::increase_skills()
{
	std::string input{};
	char temp_symbol{};

	do
	{

		system("CLS");
		std::cout << "Level points left: " << leveling_points << std::endl << std::endl;

		std::cout << "Choose option to increase skills:" << std::endl;
		std::cout << "S - Strength(+50 HP) - " << this->strength << std::endl;
		std::cout << "A - Agility(+1 Move Point) - " << this->agility << std::endl;
		std::cout << "C - Accuracy(+1 Accuracy to every shot) - " << this->additional_accuracy << std::endl;
		std::cout << "T - Stealth(Helps in hiding) - " << this->stealth << std::endl << std::endl;
		std::cout << "Q - Back" << std::endl << std::endl;

		std::cout << std::endl << "Choose skill: ";

		std::getline(std::cin, input);
		temp_symbol = input[0];
		temp_symbol = toupper(temp_symbol);

		system("CLS");

		switch (temp_symbol)
		{
		case '-':
		{
			cheats(input.substr(1, input.size()));
			break;
		}
		case 'S':
		{
			if (leveling_points >= 1)
			{
				increase_strength(1);
			}
			else
			{
				std::cout << "You need more level points!";
				Sleep(1000);
			}
			break;
		}
		case 'A':
		{
			if (leveling_points >= 1)
			{
				increase_agility(1);
			}
			else
			{
				std::cout << "You need more level points!";
				Sleep(1000);
			}
			break;
		}
		case 'C':
		{
			if (leveling_points >= 1)
			{
				increase_accuracy(1);
			}
			else
			{
				std::cout << "You need more level points!";
				Sleep(1000);
			}
			break;
		}
		case 'T':
		{
			if (leveling_points >= 1)
			{
				increase_stealth(1);
			}
			else
			{
				std::cout << "You need more level points!";
				Sleep(1000);
			}
			break;
		}
		}

	} while (temp_symbol != 'Q');

}

void MainCharacter::increase_agility(int lvl_points)
{
	system("CLS");
	agility += lvl_points;
	move_points += lvl_points;
	leveling_points -= lvl_points;
	std::cout << "Agility increased!";
	Sleep(1000);
}

void MainCharacter::increase_strength(int lvl_points)
{
	system("CLS");
	strength += lvl_points;
	max_health += (50 * lvl_points);
	health += (50 * lvl_points);
	leveling_points -= lvl_points;
	std::cout << "Strength increased!";
	Sleep(1000);
}

void MainCharacter::increase_accuracy(int lvl_points)
{
	system("CLS");
	additional_accuracy += lvl_points;
	leveling_points -= lvl_points;
	std::cout << "Accuracy increased!";
	Sleep(1000);
}

void MainCharacter::increase_stealth(int lvl_points)
{
	system("CLS");
	stealth += lvl_points;
	leveling_points -= lvl_points;
	std::cout << "Stealth increased!";
	Sleep(1000);
}



void MainCharacter::cheats(std::string code)
{
	if (code.substr(0, 9) == "setweapon")
	{
		for (auto &w : BattleMode::weapon_list)
		{
			std::string input_weapon_model = code.substr(10, code.size());
			std::string temp_weapon_model = w.get_model();

			for (auto &s : input_weapon_model)
				s = toupper(s);

			for (auto &s : temp_weapon_model)
				s = toupper(s);

			if (temp_weapon_model == input_weapon_model)
			{
				this->set_weapon(&w);
			}
		}
	}
	else if (code.substr(0, 3) == "lvl")
	{
		if (code.size() == 3)
		{
			increase_lvl(1);
		}
		else
		{
			int temp = stoi(code.substr(4, code.size()));
			increase_lvl(temp);
		}
	}
	else if (code.substr(0, 7) == "agility")
	{
		if (code.size() == 7)
		{
			leveling_points++;
			increase_agility(1);
		}
		else
		{
			int temp = stoi(code.substr(8, code.size()));
			leveling_points += temp;
			increase_agility(temp);
		}
	}
	else if (code.substr(0, 8) == "strength")
	{
		if (code.size() == 8)
		{
			leveling_points++;
			increase_strength(1);
		}
		else
		{
			int temp = stoi(code.substr(9, code.size()));
			leveling_points += temp;
			increase_strength(temp);
		}
	}
	else if (code.substr(0, 8) == "accuracy")
	{
		if (code.size() == 8)
		{
			leveling_points++;
			increase_accuracy(1);
		}
		else
		{
			int temp = stoi(code.substr(9, code.size()));
			leveling_points += temp;
			increase_accuracy(temp);
		}
	}
	else if (code.substr(0, 7) == "stealth")
	{
		if (code.size() == 7)
		{
			leveling_points++;
			increase_stealth(1);
		}
		else
		{
			int temp = stoi(code.substr(8, code.size()));
			leveling_points += temp;
			increase_stealth(temp);
		}
	}
}



void MainCharacter::increase_karma(int karma_difference)
{
	karma = karma + karma_difference;
}

int MainCharacter::get_karma()
{
	return this->karma;
}


void MainCharacter::move(int bf_size, BattleField * in_battle_field)
{
	std::vector <std::vector <char>> battle_field_copy = in_battle_field->get_grid_copy();
	float length{};

	for (int i = 0; i < bf_size; i++)
	{
		for (int j = 0; j < bf_size; j++)
		{
			if (battle_field_copy.at(i).at(j) == '0')
			{
				BattleField::path_finding.GetPath(Vector2D(0, 0), Vector2D(bf_size - 1, bf_size - 1), this->get_pos_in_battle(), Vector2D(i, j), BattleField::Obstacles, length);
				length = length * 10;

				int temp_length = static_cast<int>(length);

				if (temp_length <= move_points * 10) battle_field_copy.at(i).at(j) = 'X';
			}
		}
	}

	int point_x{};
	int point_y{};
	bool choosement_is_valid{ false };

	do
	{
		system("CLS");
		in_battle_field->visualise_grid(battle_field_copy);
		std::cout << "\n\nX - available to move.";
		std::cout << "\n\nEnter point to move(X, Y) separated by space: ";
		std::cin >> point_x >> point_y;
		if (point_x < bf_size && point_x >= 0 && point_y < bf_size && point_y >= 0)
		{
			if (battle_field_copy[point_x][point_y] == 'X') choosement_is_valid = true;
		}
	} while (!choosement_is_valid);

	this->move_to(point_x, point_y, bf_size, in_battle_field);
}

void MainCharacter::move_to(int X, int Y, int bf_size, BattleField * in_battle_field)
{

	float length;
	std::queue <Vector2D> character_path = BattleField::path_finding.GetPath(Vector2D(0, 0), Vector2D(bf_size - 1, bf_size - 1), pos_in_battle, Vector2D(X, Y), BattleField::Obstacles, length);

	queue_reverse(character_path);

	system("CLS");
	in_battle_field->visualise_grid();

	move_points = move_points * 10;
	while (true)
	{
		move_points -= static_cast<int>(pos_in_battle.get_distance(character_path.front().get_pos_x(), character_path.front().get_pos_y()) * 10);
		if (move_points < 0) break;
		pos_in_battle = character_path.front();
		character_path.pop();

		Sleep(500);
		in_battle_field->refresh();
		system("CLS");
		in_battle_field->visualise_grid();
		if (character_path.empty()) break;

	}

	move_points = move_points / 10;
	system("CLS");
	std::cout << this->name << " moved to (" << pos_in_battle.get_pos_x() << "; " << pos_in_battle.get_pos_y() << ")" << std::endl << std::endl;
	std::cin.ignore();
}

void MainCharacter::on_attack(Character * target, BattleField * in_battle_field)
{

	int distance_bonus{};
	if (pos_in_battle.get_distance(target->get_pos_x(), target->get_pos_y()) < using_weapon->get_distance())
	{
		distance_bonus = 10;
	}
	else if (pos_in_battle.get_distance(target->get_pos_x(), target->get_pos_y()) == using_weapon->get_distance())
	{
		distance_bonus = 0;
	}
	else
	{
		distance_bonus = -5;
	}

	system("CLS");

	bool miss{ false };

	if (using_weapon->get_weapon_type() == WeaponType::Melee && get_distance(target->get_pos_in_battle().get_pos_x(), target->get_pos_in_battle().get_pos_y()) < 1.5)
	{
		move_points -= 1;
		if (target->get_alive_status())
		{
			std::cout << this->name << " attacks " << target->name << std::endl << std::endl;
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			std::cout << target->name << " takes " << using_weapon->get_damage() << " damage" << std::endl << std::endl;
			in_battle_field->refresh();
		}
		else
		{
			std::cout << this->name << " attacks " << target->name << std::endl << std::endl;
			std::cout << target->name << " is already dead!" << std::endl << std::endl;
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
		}
	}
	else if (using_weapon->get_weapon_type() == WeaponType::Melee)
	{
		std::cout << "You need to get closer!" << std::endl << std::endl;
	}

	if (using_weapon->get_weapon_type() == WeaponType::Range && move_points >= 2)
	{
		move_points -= 2;
		if (fire_line_closed(target, in_battle_field))
		{
			std::cout << this->name << " attacks " << target->name << std::endl << std::endl;
			std::cout << this->name << " shot an obstacle!" << std::endl << std::endl;
			using_weapon->use_weapon(target, -100, name, miss);
			in_battle_field->refresh();
		}
		else if (target->get_alive_status())
		{
			std::cout << this->name << " attacks " << target->name << std::endl << std::endl;
			using_weapon->use_weapon(target, distance_bonus + additional_accuracy, name, miss);

			if (!miss)
				std::cout << target->name << " takes " << using_weapon->get_damage() << " damage" << std::endl << std::endl;
			if (miss)
				std::cout << this->name << " missed" << std::endl << std::endl;

			in_battle_field->refresh();
		}
		else 
		{
			std::cout << this->name << " attacks " << target->name << std::endl << std::endl;
			std::cout << target->name << " is already dead!" << std::endl << std::endl;
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
		}
	}
	else if (using_weapon->get_weapon_type() == WeaponType::Range)
	{
		std::cout << "You need more move points!" << std::endl << std::endl;
	}

	std::cin.ignore();

}

void MainCharacter::attack(std::vector <Enemy> &enemies, BattleField * in_battle_field)
{

	char input_number{};
	int enemy_number{};
	bool break_loop{false};

	do
	{
		system("CLS");
		in_battle_field->visualise_grid();
	
		std::cout << "\n\nQ - Back" << std::endl;
		std::cout << "\nChoose enemy number to attack: ";

		std::cin >> input_number;
		input_number = toupper(input_number);


		if (input_number == 'Q') break;

		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (input_number == enemies.at(i).get_symbol())
			{
				enemy_number = i;
				break_loop = true;
				break;
			}
		}

		if (break_loop) break;

	} while (true);

	if (input_number != 'Q')
	{
		on_attack(&enemies.at(enemy_number), in_battle_field);
	}

}

void MainCharacter::set_weapon(Weapon * new_weapon)
{
	if (new_weapon->get_weapon_type() == WeaponType::Range)
	{
		primary_weapon = new_weapon;
		using_weapon = new_weapon;
		if (secondary_weapon == nullptr)
			secondary_weapon = &BattleMode::weapon_list.at(4);
	}
	else if (new_weapon->get_weapon_type() == WeaponType::Melee)
	{
		secondary_weapon = new_weapon;
		using_weapon = new_weapon;
		if (primary_weapon == nullptr)
			primary_weapon = &BattleMode::weapon_list.at(4);
	}
}

void MainCharacter::die()
{
	this->alive = false;
	show_out_message(this->name + " died");
	pos_in_battle = Vector2D(1000, 1000);
	BattleField::Objects.remove(this);
}

void MainCharacter::swap_weapon()
{
	if (primary_weapon != nullptr && secondary_weapon != nullptr)
	{
		if (primary_weapon == using_weapon)
			using_weapon = secondary_weapon;
		else if (secondary_weapon == using_weapon)
			using_weapon = primary_weapon;
	}
}

void MainCharacter::leave_weapon()
{
	primary_weapon = &BattleMode::weapon_list.at(4);
	secondary_weapon = &BattleMode::weapon_list.at(4);
	using_weapon = &BattleMode::weapon_list.at(4);
}

void MainCharacter::set_health(int health_in)
{
	max_health = health_in;
	health = health_in;
};

void MainCharacter::set_lvl_points(int lvl_points) 
{
	leveling_points = lvl_points;
};

void MainCharacter::set_strength(int lvl_points)
{
	strength = lvl_points;
};

void MainCharacter::set_accuracy(int lvl_points)
{
	additional_accuracy = lvl_points;
};

void MainCharacter::set_stealth(int lvl_points)
{
	stealth = lvl_points;
};

void MainCharacter::set_karma(int karma_level)
{
	karma = karma_level;
};


int MainCharacter::get_strength()
{
	return this->strength;
};

int MainCharacter::get_additiona_accuracy() 
{
	return this->additional_accuracy;
};

int MainCharacter::get_stealth() 
{
	return this->stealth;
};

int MainCharacter::get_lvl_points()
{
	return this->leveling_points;
};

int MainCharacter::get_syringes_count()
{
	return this->syringes;
};


MainCharacter::MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon)
{
	alive = true;
	name = input_name;
	health = input_hp;
	max_health = health;
	if (std_using_weapon != nullptr)
	{
		if (std_using_weapon->get_weapon_type() == WeaponType::Range)
		{
			primary_weapon = std_using_weapon;
			secondary_weapon = new MeleeWeapon("Hands", 30, 5);
		}
		else
		{
			primary_weapon = new MeleeWeapon("Hands", 30, 5);
			secondary_weapon = std_using_weapon;
		}
	}
	using_weapon = std_using_weapon;
	move_points = 6;
	agility = 6;
	this->object_type = "Main Character";
}

MainCharacter::MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon, int input_agility)
{
	alive = true;
	name = input_name;
	health = input_hp;
	max_health = health;
	if (std_using_weapon != nullptr)
	{
		if (std_using_weapon->get_weapon_type() == WeaponType::Range)
		{
			primary_weapon = std_using_weapon;
			secondary_weapon = new MeleeWeapon("Hands", 30, 5);
		}
		else
		{
			primary_weapon = new MeleeWeapon("Hands", 30, 5);
			secondary_weapon = std_using_weapon;
		}
	}
	using_weapon = std_using_weapon;
	move_points = input_agility;
	agility = input_agility;
	this->object_type = "Main Character";
}

MainCharacter::MainCharacter(std::string input_name, int input_hp, Weapon * std_using_weapon, MeleeWeapon * std_secondary_weapon)
{
	alive = true;
	name = input_name;
	health = input_hp;
	max_health = health;
	primary_weapon = std_using_weapon;
	secondary_weapon = std_secondary_weapon;
	using_weapon = std_using_weapon;
	move_points = 6;
	agility = 6;
	this->object_type = "Main Character";
}

MainCharacter::MainCharacter(std::string input_name, int input_hp, Weapon *std_using_weapon, MeleeWeapon *std_secondary_weapon, int input_agility)
{
	alive = true;
	name = input_name;
	health = input_hp;
	max_health = health;
	primary_weapon = std_using_weapon;
	secondary_weapon = std_secondary_weapon;
	using_weapon = std_using_weapon;
	move_points = input_agility;
	agility = input_agility;
	this->object_type = "Main Character";
}

MainCharacter::MainCharacter() : MainCharacter("Main Character", 150, nullptr, nullptr) {};