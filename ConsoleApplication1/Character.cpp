#include "Character.h"
#include "Object.h"
#include "Vector2D.h"
#include "BattleField.h"

void Character::raise_agility(int agility_plus_count)
{
	agility += agility_plus_count;
	move_points = agility;
}

void Character::set_agility(int agility_set_count)
{
	agility = agility_set_count;
	move_points = agility;
}

void Character::set_weapon(Weapon *new_weapon)
{
	using_weapon = new_weapon;
}

void Character::attack(Character *target, BattleField * in_battle_field)
{
	while (this->move_points_info() > 1)
	{
		system("CLS");
		this->on_attack(target, in_battle_field);
		if (this->get_weapon_type() == WeaponType::Melee && this->get_distance(target->get_pos_x(),target->get_pos_y()) > 1.5) break;
		Sleep(1000);
		system("CLS");
	}
}

void Character::on_attack(Character *target, BattleField * in_battle_field)
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
	
	bool miss{ false };
	std::string out_message;

	if (using_weapon->get_weapon_type() == WeaponType::Melee && get_distance(target->get_pos_in_battle().get_pos_x(), target->get_pos_in_battle().get_pos_y()) < 1.5)
	{
		move_points -= 1;
		if (target->get_alive_status())
		{
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
			in_battle_field->visualise_grid();

			out_message = this->name + " attacks " + target->name;
			Object::show_out_message(out_message);

			out_message = target->name + " takes " + std::to_string(using_weapon->get_damage()) + " damage";
			Object::show_out_message(out_message);
		}
		else
		{
			out_message = this->name + " attacks " + target->name;
			Object::show_out_message(out_message);

			out_message = target->name + " is already dead!";
			Object::show_out_message(out_message);

			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
		}
	}
	else if (using_weapon->get_weapon_type() == WeaponType::Melee)
	{
		using_weapon->use_weapon(target, distance_bonus, name, miss);
		in_battle_field->refresh();
		in_battle_field->visualise_grid();

		out_message = "You need to get closer!";
		Object::show_out_message(out_message);
	}
	
	if (using_weapon->get_weapon_type() == WeaponType::Range)
	{
		move_points -= 2;
		if (fire_line_closed(target, in_battle_field))
		{
			out_message = this->name + " attacks " + target->name;
			Object::show_out_message(out_message);

			out_message = this->name + " shot an obstacle!";
			Object::show_out_message(out_message);

			using_weapon->use_weapon(target, -100, name, miss);
			in_battle_field->refresh();
		}
		else if (target->get_alive_status())
		{
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
			in_battle_field->visualise_grid();

			out_message = this->name + " attacks " + target->name;
			Object::show_out_message(out_message);

			if(!miss)
				out_message = target->name + " takes " + std::to_string(using_weapon->get_damage()) + " damage";
			if (miss)
				out_message = this->name + " missed";

			Object::show_out_message(out_message);
		}
		else
		{
			out_message = this->name + " attacks " + target->name;
			Object::show_out_message(out_message);

			out_message = target->name + " is already dead!";
			Object::show_out_message(out_message);
			using_weapon->use_weapon(target, distance_bonus, name, miss);
			in_battle_field->refresh();
		}
	} 
}

void Character::get_health()
{
	std::cout << this->name << ": " << this->health << "HP" << std::endl;
}

int Character::get_health_int()
{
	return this->health;
}

void Character::get_info()
{
	std::cout << this->name << ": " << this->health << "HP. " << "Movement points: " << this->move_points << " Using weapon: ";
	this->get_weapon_info();
}

void Character::get_weapon_info()
{
	using_weapon->get_weapon_info();
}

char Character::get_symbol()
{
	return this->name[0];
}

void Character::set_on_pos(int X, int Y)
{
	Vector2D new_pos(X, Y);
	this->pos_in_battle = new_pos;
}

void Character::move(Object & main_character, int bf_size, BattleField * in_battle_field)
{

	if (this->get_distance(main_character.get_pos_in_battle().get_pos_x(), main_character.get_pos_in_battle().get_pos_y()) > this->using_weapon->get_distance())
	{
		std::queue <Vector2D> best_positions = BattleField::grid_query_component.GetBestPositions(this->get_pos_in_battle(), main_character.get_pos_in_battle(), this->get_weapon_distance() - 1, BattleField::Objects, Vector2D(0, 0), Vector2D(8, 8));

		Vector2D best_pos;

		while (true)
		{
			if (!in_battle_field->check_node(best_positions.front()))
			{
				best_pos = best_positions.front();
				break;
			}
			else
			{
				best_positions.pop();
			}
		}

		this->move_to(best_pos.get_pos_x(), best_pos.get_pos_y(), bf_size, in_battle_field);
	}

}

void Character::move_to(int X, int Y, int bf_size, BattleField * in_battle_field)
{

	float length;
	std::queue <Vector2D> character_path = BattleField::path_finding.GetPath(Vector2D(0, 0), Vector2D(bf_size - 1, bf_size - 1), pos_in_battle, Vector2D(X, Y), BattleField::Objects, length);
	
	queue_reverse(character_path);

	system("CLS");
	in_battle_field->visualise_grid();

	move_points = move_points * 10;
	while (true)
	{
		move_points -= static_cast<int>(pos_in_battle.get_distance(character_path.front().get_pos_x(), character_path.front().get_pos_y())*10);
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

	Object::show_out_message(this->name + " moved to (" + std::to_string(pos_in_battle.get_pos_x()) + "; " + std::to_string(pos_in_battle.get_pos_y()) + ")");
	
	Sleep(1200);

}

int Character::move_points_info()
{
	return this->move_points;
}

int Character::get_weapon_fire_rate()
{
	return using_weapon->get_fire_rate();
}

int Character::get_pos_x()
{
	return pos_in_battle.get_pos_x();
}

int Character::get_pos_y()
{
	return pos_in_battle.get_pos_y();
}

double Character::get_distance(int position_x, int position_y)
{
	return pos_in_battle.get_distance(position_x, position_y);
}

WeaponType Character::get_weapon_type()
{
	return using_weapon->get_weapon_type();
}

int Character::get_weapon_distance()
{
	return using_weapon->get_distance();
}

Vector2D Character::get_pos_in_battle()
{
	return pos_in_battle;
}

void Character::reset_move_points()
{
	move_points = agility;
}

Weapon * Character::get_weapon()
{
	return using_weapon;
}

int Character::get_agility()
{
	return this->agility;
}

void Character::increase_loyalty(int loyalty_difference)
{
	loyalty_level = loyalty_level + loyalty_difference;
}

void Character::get_killed()
{
	health = 0;
	alive = false;
}

void Character::set_life_status(bool in)
{
	alive = in;
}

void Character::set_health(int health_in)
{
	health = health_in;
}

void Character::set_max_health(int health_in)
{
	health = health_in;
}

int Character::get_max_health()
{
	return this->max_health;
}

void Character::set_loyalty(int loyalty)
{
	loyalty_level = loyalty;
}

int Character::get_loyalty()
{
	return this->loyalty_level;
}

void Character::reset_health()
{
	health = max_health;
}

bool Character::fire_line_closed(Character * target, BattleField * in_battle_field)
{
	NormalizedVec targer_line{ this->get_pos_in_battle().get_normalized_vec(target->get_pos_in_battle()) };
	double distance = this->get_distance(target->get_pos_x(), target->get_pos_y());

	for (auto o : BattleField::Obstacles)
	{
		double obs_dist = this->get_distance(o->get_pos_in_battle().get_pos_x(), o->get_pos_in_battle().get_pos_y());

		if (targer_line == this->get_pos_in_battle().get_normalized_vec(o->get_pos_in_battle()) && obs_dist < distance)
			return true;
	}
	return false;
}

void Character::die()
{
	Object::die();
	BattleField::Objects.remove(this);
}

void Character::queue_reverse(std::queue <Vector2D> &in_queue)
{
	std::stack <Vector2D> stk;

	//Queue reverse
	while (!in_queue.empty())
	{
		Vector2D data = in_queue.front();
		in_queue.pop();
		stk.push(data);
	}
	while (!stk.empty())
	{
		Vector2D data = stk.top();
		stk.pop();
		in_queue.push(data);
	}
	//
}

Character::Character(std::string name_in, Weapon * using_weapon_in, int health_in, int starting_loyalty_level)
{
	name = name_in;
	using_weapon = using_weapon_in;
	health = health_in;
	loyalty_level = starting_loyalty_level;
	alive = true;
}

Character::Character() : Character("TempName", nullptr, 150, 0) {};

Character::~Character() {};
