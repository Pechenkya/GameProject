#include "BattleMode.h"
#include "SpecialBattleField.h"

std::vector <Weapon> BattleMode::weapon_list;

void BattleMode::battle_mode()
{
	set_weapon_on_character();
	create_enemies();
	
	//Setting console
	system("mode con cols=200 lines=51");
	//

	if (battle_mode_type == "Common")
	{
		BattleField new_battlefield;
		new_battlefield.new_battle(main_character, group_of_enemies, obstacle_preset, surrender_status);
	}
	else if (battle_mode_type == "Special")
	{
		SpecialBattleField new_battlefield;
		new_battlefield.new_battle(main_character, group_of_enemies, obstacle_preset, surrender_status);
	}

	battle_mode_results();

	//Setting console
	system("mode con cols=130 lines=40");

}

void BattleMode::set_weapon_on_character()
{
	int user_choosement{};
	do
	{
		system("CLS");
		std::cout << "Choose your weapon." << std::endl;
		std::cout << "0 - Melee Weapon" << std::endl;
		std::cout << "1 - Firearms" << std::endl << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << i + 1 << ": " << weapon_list.at(i).get_model() << "(" << weapon_list.at(i).get_weapon_type() << ")";
			if (weapon_list.at(i).get_weapon_type() == WeaponType::Melee)
				std::cout << " !You'll battle only versus enemies with melee weapon!";
			std::cout << std::endl;
		}
		std::cout << "Enter weapon number: ";
		std::cin >> user_choosement;
		system("CLS");
	} while (user_choosement < 1 || user_choosement > weapon_list.size());
	user_choosement--;
	main_character.set_weapon(&weapon_list.at(user_choosement));
	system("CLS");
}

void BattleMode::create_enemies()
{
	if (main_character.get_weapon_type() == WeaponType::Range)
	{
		for (int i = 0; i < group_of_enemies_size; i++)
		{
			group_of_enemies.push_back(Enemy());
			group_of_enemies.at(i).name = enemy_name + " " + std::to_string(i + 1);
			if (rand() % 1000 < 300)
				group_of_enemies.at(i).set_weapon(&weapon_list.at(5));	//P250
			else if (rand() % 1000 < 600)
				group_of_enemies.at(i).set_weapon(&weapon_list.at(3));	//Kukri
			else
				group_of_enemies.at(i).set_weapon(&weapon_list.at(4));	//Hands
		}
	}
	else if (main_character.get_weapon_type() == WeaponType::Melee)
	{
		for (int i = 0; i < group_of_enemies_size; i++)
		{
			group_of_enemies.push_back(Enemy());
			group_of_enemies.at(i).name = enemy_name + " " + std::to_string(i + 1);
			if (rand() % 1000 < 600)
				group_of_enemies.at(i).set_weapon(&weapon_list.at(4));	//Hands
			else
				group_of_enemies.at(i).set_weapon(&weapon_list.at(3));	//Kukri
		}
	}
}

void BattleMode::create_weapons()
{
	//Only for main character
	weapon_list.push_back(Firearms("Nova", 120, 60, 4, 2));				//Shotgun
	weapon_list.push_back(Firearms("AK-74", 60, 80, 9, 7));				//AR
	weapon_list.push_back(Firearms("Desert Eagle", 75, 70, 6, 5));		//Handgun
	//For everyone
	weapon_list.push_back(MeleeWeapon("Kukri", 50, 6));					//Machete
	weapon_list.push_back(MeleeWeapon("Hands", 30, 5));					//Hands
	//Only for enemies
	weapon_list.push_back(Firearms("P250", 25, 65, 7, 4));				//Handgun
}

void BattleMode::battle_mode_results()
{
	if (main_character.get_alive_status() && !surrender_status)
	{
		system("CLS");
		Object::show_out_message("Great job!");
		Object::show_out_message("You won in battle mode!");
		Object::show_out_message("Now try yourself in real game mode!");
		system("pause");
	}
	else
	{
		system("CLS");
		Object::show_out_message("Nice try!");
		Object::show_out_message("You lost in battle mode!");
		Object::show_out_message("Try again, this time you'll win!");
		system("pause");
	}
}

BattleMode::BattleMode(MainCharacter main_character_in, int group_of_enemies_size_in, std::string enemy_name_in, std::vector <Obstacle> obstacle_preset_in, std::string battle_mode_type_in)
{
	main_character = main_character_in;
	group_of_enemies_size = group_of_enemies_size_in;
	enemy_name = enemy_name_in;
	obstacle_preset = obstacle_preset_in;
	battle_mode_type = battle_mode_type_in;
}
