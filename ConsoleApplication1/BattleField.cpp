#include "BattleField.h"

//

PathfindingComponent BattleField::path_finding;
std::list <Object*> BattleField::Obstacles;
std::list <Object*> BattleField::Objects;
GridQueryComponent BattleField::grid_query_component;


//

void BattleField::new_battle(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies, std::vector <Obstacle> &obstacles, bool & surrender_status)
{

	initialize_battle(main_character, group_of_enemies, obstacles);

	main_battle_loop(main_character, group_of_enemies);

	clear();

	surrender_status = main_character_surrendered;
}

BattleField::~BattleField()
{
}

//

void BattleField::initialize_battle(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies, std::vector<Obstacle>& obstacles)
{

	fill_info_lists(main_character, group_of_enemies, obstacles);
	set_objects_on_positions(main_character, group_of_enemies);
	build_battle_field_scheme();
	battle_starting(main_character, group_of_enemies);

}

void BattleField::set_objects_on_positions(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	main_character.set_on_pos(0, (battle_field_size / 2));

	int indent = (battle_field_size - group_of_enemies.size()) / 2;
	for (size_t i = 0; i < group_of_enemies.size(); i++)
	{
		group_of_enemies.at(i).set_on_pos(battle_field_size - 1, (battle_field_size - indent - 1) - i);
	}

}



void BattleField::build_battle_field_scheme()
{

	std::vector <std::vector <char>> temp_visual_bf(battle_field_size, std::vector<char>(battle_field_size, '0'));
	for (auto t : Objects)
	{
		temp_visual_bf.at(t->get_pos_in_battle().get_pos_x()).at(t->get_pos_in_battle().get_pos_y()) = t->get_symbol();
	}
	visual_bf = temp_visual_bf;

}



void BattleField::fill_info_lists(MainCharacter& main_character, std::vector<Enemy>& group_of_enemies, std::vector<Obstacle>& obstacles)
{

	for (int i = 0; i < obstacles.size(); i++)
	{
			Objects.push_back(&obstacles.at(i));
			Obstacles.push_back(&obstacles.at(i));
	}

	for (int i = 0; i < group_of_enemies.size(); i++)
	{
		if (group_of_enemies.at(i).get_alive_status())
		{
			Objects.push_back(&group_of_enemies.at(i));
		}
	}

	Objects.push_back(&main_character);
}



void BattleField::visualise_grid()
{

	std::cout << "Y" << std::endl;

	for (int y = battle_field_size - 1; y >= 0; y--)
	{
		std::cout << y << "| ";
		for (int x = 0; x < battle_field_size; x++)
		{
			std::cout << visual_bf.at(x).at(y) << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < battle_field_size + 1; i++) std::cout << "==";
	{
		std::cout << std::endl << "0| ";
	}

	for (int i = 0; i < battle_field_size; i++)
	{
		std::cout << i << " ";
	}

	std::cout << "X" << std::endl << std::endl;

}

void BattleField::visualise_grid(std::vector <std::vector <char>> bf_copy)
{

	std::cout << "Y" << std::endl;

	for (int y = battle_field_size - 1; y >= 0; y--)
	{
		std::cout << y << "| ";
		for (int x = 0; x < battle_field_size; x++)
		{
			std::cout << bf_copy.at(x).at(y) << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < battle_field_size + 1; i++) std::cout << "==";
	{
		std::cout << std::endl << "0| ";
	}

	for (int i = 0; i < battle_field_size; i++)
	{
		std::cout << i << " ";
	}

	std::cout << "X" << std::endl << std::endl;

}

std::vector<std::vector<char>> BattleField::get_grid_copy()
{
	return visual_bf;
}



void BattleField::visualise_status(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	std::cout << "0 - Melee" << std::endl;
	std::cout << "1 - Firearms" << std::endl;
	std::cout << std::endl;

	for (auto t : group_of_enemies)
	{
		t.get_info();
	}
	std::cout << std::endl << std::endl;
	main_character.get_info();

}



void BattleField::battle_starting(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	do
	{
		system("CLS");
		visualise_grid();
		visualise_status(main_character, group_of_enemies);

		std::cout << std::endl << "Enter Y to start battle: ";
		std::getline(std::cin, input);
		temp_symbol = input[0];
		temp_symbol = toupper(temp_symbol);
	} while (temp_symbol != 'Y');

}



void BattleField::main_battle_loop(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	while(main_character.get_alive_status() && return_enemy_life_status_info(group_of_enemies) && !main_character_surrendered)
	{
		if (battle_start_status(main_character, group_of_enemies))
		{
			if (main_character_surrendered || !main_character.get_alive_status()) break;

			main_character_turn(main_character, group_of_enemies);
			main_character.reset_move_points();
			
			if (main_character_surrendered || !main_character.get_alive_status()) break;

			enemy_turn(main_character, group_of_enemies);
			reset_enemies_move_points(group_of_enemies);
		
		}
		else
		{
			if (main_character_surrendered || !main_character.get_alive_status()) break;

			enemy_turn(main_character, group_of_enemies);
			reset_enemies_move_points(group_of_enemies);

			if (main_character_surrendered || !main_character.get_alive_status()) break;

			main_character_turn(main_character, group_of_enemies);
			main_character.reset_move_points();
		
		}
	}

}





void BattleField::main_character_turn(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{
	system("CLS");

	while (main_character.move_points_info() > 0)
	{
		if (!return_enemy_life_status_info(group_of_enemies)) break;

		char user_input = user_input_in_UI(main_character, group_of_enemies);

		if (user_input == 'W') break;

		if (user_input == 'R')
		{
			main_character_surrendered = true;
			break;
		}

		process_user_selecion(main_character, group_of_enemies, user_input);
	}

	temp_symbol = ' ';
	input = " ";

	visualise_grid();
	Sleep(500);
}



void BattleField::visualise_user_choosements(MainCharacter & main_character)
{

	std::cout << "\nUse key buttons: " << std::endl;
	std::cout << "M - Move" << std::endl;
	std::cout << "A - Attack enemy";
	if (main_character.get_weapon_type() == WeaponType::Range) std::cout << "(2 move points)" << std::endl;
	if (main_character.get_weapon_type() == WeaponType::Melee) std::cout << "(1 move point)" << std::endl;
	std::cout << "S - Swap weapon" << std::endl;
	std::cout << "R - Run away" << std::endl;
	std::cout << "T - Increase skills" << std::endl;
	std::cout << "H - Heal up +50HP (1 move point and 1 syringe)" << std::endl;
	std::cout << "W - Wait(ends your turn)" << std::endl;

}



char BattleField::user_input_in_UI(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	do
	{
		visualise_grid();
		visualise_status(main_character, group_of_enemies);
		std::cout << std::endl;

		visualise_user_choosements(main_character);
		std::cout << std::endl << "Enter your choosement: ";
		
		std::getline(std::cin, input);
		temp_symbol = input[0];
		temp_symbol = toupper(temp_symbol);

		if (temp_symbol == '-')
			main_character.cheats(input.substr(1, input.size()));

		system("CLS");


	} while (temp_symbol != 'M' && temp_symbol != 'A' && temp_symbol != 'S' && temp_symbol != 'R' && temp_symbol != 'H' && temp_symbol != 'W' && temp_symbol != 'T');

	return temp_symbol;

}

void BattleField::process_user_selecion(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies, char us_input)
{

	if (us_input == 'M') main_character.move(battle_field_size, this);
	if (us_input == 'A') main_character.attack(group_of_enemies, this);
	if (us_input == 'H') main_character.healup();
	if (us_input == 'S') main_character.swap_weapon();
	if (us_input == 'T') main_character.increase_skills();

}



void BattleField::enemy_turn(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{

	for (size_t i = 0; i < group_of_enemies.size(); i++)
	{
		if (group_of_enemies.at(i).get_alive_status() && main_character.get_alive_status())
		{
			group_of_enemies.at(i).move(main_character, battle_field_size, this);
			group_of_enemies.at(i).attack(&main_character, this);
		}
	}

	Sleep(500);
}




void BattleField::reset_enemies_move_points(std::vector<Enemy>& group_of_enemies)
{

	for(int i = 0; i < group_of_enemies.size(); i++)
	{
		group_of_enemies.at(i).reset_move_points();
	}

}

//

bool BattleField::return_enemy_life_status_info(std::vector<Enemy>& group_of_enemies)
{

	int death_counter{};
	for (auto t : group_of_enemies)
		if (!t.get_alive_status()) death_counter++;

	if (death_counter == group_of_enemies.size()) return false;
	else return true;

}

bool BattleField::check_node(Vector2D pos)
{

	for (auto t : BattleField::Objects)
		if (t->get_pos_in_battle() == pos)
		{
			return true;
		}
	return false;

}

bool BattleField::battle_start_status(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{
	
	for (size_t i = 0; i < group_of_enemies.size(); i++)
	{
		if (group_of_enemies.at(i).get_weapon_fire_rate() > main_character.get_weapon_fire_rate())
		{
			return false;
		}
	}

	return true;

}

//

void BattleField::refresh()
{

	build_battle_field_scheme();

}

//

void BattleField::clear()
{

	BattleField::Obstacles.clear();
	BattleField::Objects.clear();

}
