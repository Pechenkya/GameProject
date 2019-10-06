#include "MainMenu.h"

std::vector <Obstacle> MainMenu::special_obstacle_preset;

std::vector <std::vector <Obstacle>> MainMenu::obstacle_presets;

void MainMenu::user_menu()
{
	//Create obstacle presets
	create_obstacle_presets();
	//
	BattleMode::create_weapons();

	char user_input_key{};
	welcome_screen();
	while (true)
	{
		do
		{
			system("CLS");
			std::cout << "Welcome to <Game_Name>!" << std::endl << std::endl;
			std::cout << "P - Play" << std::endl;
			std::cout << "O - Options" << std::endl << std::endl;
			std::cout << "Q - Quit" << std::endl << std::endl;
			std::cout << "Enter your opinion: ";
			std::cin >> user_input_key;
			user_input_key = toupper(user_input_key);
			system("CLS");
		} while (user_input_key != 'P' && user_input_key != 'Q' && user_input_key != 'O');

		if (user_input_key == 'Q') break;

		if (user_input_key == 'O') options();

		if (user_input_key == 'P')
		{
			do
			{
				std::cout << "S - Story Mode" << std::endl;
				std::cout << "B - Battle mode" << std::endl << std::endl;
				std::cout << "Q - Back" << std::endl << std::endl;
				std::cout << "Enter your opinion: ";
				std::cin >> user_input_key;
				user_input_key = toupper(user_input_key);
				system("CLS");
			} while (user_input_key != 'S' && user_input_key != 'B' && user_input_key != 'Q');

			if (user_input_key == 'S') enter_story_mode();

			if (user_input_key == 'B') enter_battle_mode();
		}
	}
}

void MainMenu::welcome_screen()
{
	MainMenu::show_out_message("Welcome to the test battle program!");
	Sleep(500);
	MainMenu::show_out_message("Remember this is only test program variant!");
	Sleep(500);
	MainMenu::show_out_message("If you find some bugs or problems, show it to me, please!");
	Sleep(500);
	system("pause");
	system("CLS");
}

void MainMenu::enter_battle_mode()
{
	system("CLS");
	Weapon * temp_weapon = nullptr;
	MainCharacter MC(main_character_name, 150, temp_weapon);
	MC.add_syringes(10);
	int count_of_enemies{};
	do
	{
		std::cout << "Enter count of enemies(1-9): ";
		std::cin >> count_of_enemies;
		system("CLS");
	} while (count_of_enemies < 1 || count_of_enemies > 9);
	BattleMode new_bm(MC, count_of_enemies, enemy_name, using_obstacle_preset, battle_field_type);
	new_bm.battle_mode();
}

void MainMenu::options()
{
	do
	{
		std::cout << "S - Story Mode options" << std::endl;
		std::cout << "B - Battle Mode options" << std::endl << std::endl;
		std::cout << "Q - Back" << std::endl << std::endl;
		std::cout << "Enter your opinion: ";
		std::cin >> user_input_key;
		user_input_key = toupper(user_input_key);
		system("CLS");
	} while (user_input_key != 'S' && user_input_key != 'B' && user_input_key != 'Q');

	if (user_input_key == 'B') battle_mode_options();

	if (user_input_key == 'S') story_mode_options();
}

void MainMenu::battle_mode_options()
{
	do
	{
		std::cout << "C - Change Character Name" << std::endl;
		std::cout << "E - Change Battle Mode Enemy Name" << std::endl;
		std::cout << "L - Change Location in Battle Mode" << std::endl;
		std::cout << "B - Change Battle Field Type" << std::endl << std::endl;
		std::cout << "Q - Back" << std::endl << std::endl;
		std::cout << "Enter your opinion: ";
		std::cin >> user_input_key;
		user_input_key = toupper(user_input_key);
		system("CLS");
	} while (user_input_key != 'C' && user_input_key != 'E' && user_input_key != 'L' && user_input_key != 'Q' && user_input_key != 'B');

	if (user_input_key == 'C') change_main_character_name();

	if (user_input_key == 'E') change_enemy_name();

	if (user_input_key == 'L') change_obstacle_preset();
	
	if (user_input_key == 'B') change_battle_field_type();
}

void MainMenu::story_mode_options()
{
	do
	{
		std::cout << "R - Reset saves" << std::endl << std::endl;
		std::cout << "Q - Back" << std::endl << std::endl;
		std::cout << "Enter your opinion: ";
		std::cin >> user_input_key;
		user_input_key = toupper(user_input_key);
		system("CLS");
	} while (user_input_key != 'R' && user_input_key != 'Q');

	if (user_input_key == 'R') StoryMode::reset_saves();
}

void MainMenu::change_main_character_name()
{
	std::string user_input{};
	std::cout << "Now using name: " << main_character_name << std::endl << std::endl;
	std::cout << "Enter new name for Main Character." << std::endl;
	std::cout << "Not recommended using names starting with: 0, W, or any numbers/symbols(.,\|/)!" << std::endl << std::endl;
	std::cout << "Q - Back" << std::endl << std::endl;
	std::cout << "Enter new name: ";
	std::cin.ignore();
	std::getline(std::cin, user_input);
	system("CLS");
	if (user_input != "Q" && user_input != "q") main_character_name = user_input;
}

void MainMenu::change_enemy_name()
{
	std::string user_input{};
	std::cout << "Now using name: " << enemy_name << std::endl << std::endl;
	std::cout << "Enter new name for Enemies." << std::endl;
	std::cout << "Not recommended using names starting with: 0, W, or any numbers/symbols(.,\|/)!" << std::endl << std::endl;
	std::cout << "Q - Back" << std::endl;
	std::cout << "Enter new name: ";
	std::cin.ignore();
	std::getline(std::cin, user_input);
	system("CLS");
	if (user_input != "Q" && user_input != "q") enemy_name = user_input;
}

void MainMenu::change_battle_field_type()
{

	do
	{
		std::cout << "Now Battle Field Type: " << battle_field_type << std::endl << std::endl;

		std::cout << "1 - Common" << std::endl;
		std::cout << "2 - Special" << std::endl << std::endl;
		std::cout << "Q - Back" << std::endl;

		std::cin >> user_input_key;
		user_input_key = toupper(user_input_key);
	} while (user_input_key != '1' && user_input_key != '2' && user_input_key != 'Q');

	if (user_input_key == '1')
	{
		battle_field_type = "Common";
		using_obstacle_preset = obstacle_presets.at(obstacle_preset_num);
		using_obstacle_preset_name = obstacle_preset_names.at(obstacle_preset_num);
	}

	if (user_input_key == '2')
	{
		battle_field_type = "Special";
		using_obstacle_preset = special_obstacle_preset;
	}
}

void MainMenu::change_obstacle_preset()
{
	int user_input_int{};
	do
	{
		std::cout << "Now Battle Field Type: " << battle_field_type << std::endl << std::endl;
		std::cout << "Now using location: " << using_obstacle_preset_name << std::endl << std::endl;
		for (int i = 0; i < obstacle_presets.size(); i++)
		{
			std::cout << i + 1 << " - " << obstacle_preset_names.at(i) << std::endl;
		}

		std::cout << std::endl << "Q - Back" << std::endl;
		std::cin >> user_input_key;
		user_input_key = toupper(user_input_key);
		std::string temp_string;
		temp_string += user_input_key;
		if (user_input_key != 'Q') user_input_int = atoi(temp_string.c_str());

		system("CLS");
	} while (user_input_int <= 0 && user_input_int > obstacle_presets.size() && user_input_key != 'Q');

	if (user_input_key != 'Q')
	{
		if(battle_field_type == "Common")
			using_obstacle_preset = obstacle_presets.at(user_input_int - 1);

		using_obstacle_preset_name = obstacle_preset_names.at(user_input_int - 1);
		obstacle_preset_num = user_input_int - 1;
	}
	
}

void MainMenu::create_obstacle_presets()
{
	//Strange looking code // Better create cfg file
	//Preset 1 (Wasteland)
	std::vector <Obstacle> preset1;
	obstacle_presets.push_back(preset1);
	obstacle_preset_names.push_back("Wasteland");

	//Preset 2 (Abandoned building)
	std::vector <Obstacle> preset2;
	preset2.push_back(Obstacle(Vector2D(4, 7)));
	preset2.push_back(Obstacle(Vector2D(4, 6)));
	preset2.push_back(Obstacle(Vector2D(5, 6)));
	preset2.push_back(Obstacle(Vector2D(5, 5)));
	preset2.push_back(Obstacle(Vector2D(3, 4)));
	preset2.push_back(Obstacle(Vector2D(3, 3)));
	preset2.push_back(Obstacle(Vector2D(5, 2)));
	preset2.push_back(Obstacle(Vector2D(5, 1)));
	preset2.push_back(Obstacle(Vector2D(4, 1)));
	preset2.push_back(Obstacle(Vector2D(2, 1)));
	preset2.push_back(Obstacle(Vector2D(2, 0)));
	obstacle_presets.push_back(preset2);
	obstacle_preset_names.push_back("Abandoned building");

	//Preset 3 (Factory)
	std::vector <Obstacle> preset3;
	preset3.push_back(Obstacle(Vector2D(2, 8)));
	preset3.push_back(Obstacle(Vector2D(5, 6)));
	preset3.push_back(Obstacle(Vector2D(3, 5)));
	preset3.push_back(Obstacle(Vector2D(3, 4)));
	preset3.push_back(Obstacle(Vector2D(5, 4)));
	preset3.push_back(Obstacle(Vector2D(5, 3)));
	preset3.push_back(Obstacle(Vector2D(6, 3)));
	preset3.push_back(Obstacle(Vector2D(5, 2)));
	preset3.push_back(Obstacle(Vector2D(2, 2)));
	preset3.push_back(Obstacle(Vector2D(2, 1)));
	obstacle_presets.push_back(preset3);
	obstacle_preset_names.push_back("Factory");

	//Preset 4 (Factory 2)
	std::vector <Obstacle> preset4;
	preset4.push_back(Obstacle(Vector2D(3, 8)));
	preset4.push_back(Obstacle(Vector2D(3, 7)));
	preset4.push_back(Obstacle(Vector2D(6, 7)));
	preset4.push_back(Obstacle(Vector2D(2, 5)));
	preset4.push_back(Obstacle(Vector2D(3, 5)));
	preset4.push_back(Obstacle(Vector2D(3, 4)));
	preset4.push_back(Obstacle(Vector2D(5, 4)));
	preset4.push_back(Obstacle(Vector2D(5, 3)));
	preset4.push_back(Obstacle(Vector2D(3, 1)));
	preset4.push_back(Obstacle(Vector2D(4, 1)));
	preset4.push_back(Obstacle(Vector2D(3, 0)));
	obstacle_presets.push_back(preset4);
	obstacle_preset_names.push_back("Factory 2");

	//Preset 5 (Docks)
	std::vector <Obstacle> preset5;
	preset5.push_back(Obstacle(Vector2D(4, 8)));
	preset5.push_back(Obstacle(Vector2D(4, 7)));
	preset5.push_back(Obstacle(Vector2D(3, 7)));
	preset5.push_back(Obstacle(Vector2D(6, 6)));
	preset5.push_back(Obstacle(Vector2D(6, 5)));
	preset5.push_back(Obstacle(Vector2D(3, 5)));
	preset5.push_back(Obstacle(Vector2D(2, 5)));
	preset5.push_back(Obstacle(Vector2D(1, 3)));
	preset5.push_back(Obstacle(Vector2D(5, 3)));
	preset5.push_back(Obstacle(Vector2D(5, 2)));
	preset5.push_back(Obstacle(Vector2D(3, 2)));
	preset5.push_back(Obstacle(Vector2D(3, 1)));
	preset5.push_back(Obstacle(Vector2D(2, 1)));
	preset5.push_back(Obstacle(Vector2D(6, 0)));
	obstacle_presets.push_back(preset5);
	obstacle_preset_names.push_back("Docks");

	//Preset 6 (Close Quarters)
	std::vector <Obstacle> preset6;
	preset6.push_back(Obstacle(Vector2D(4, 8)));
	preset6.push_back(Obstacle(Vector2D(4, 7)));
	preset6.push_back(Obstacle(Vector2D(3, 7)));
	preset6.push_back(Obstacle(Vector2D(6, 6)));
	preset6.push_back(Obstacle(Vector2D(6, 5)));
	preset6.push_back(Obstacle(Vector2D(3, 5)));
	preset6.push_back(Obstacle(Vector2D(2, 5)));
	preset6.push_back(Obstacle(Vector2D(1, 3)));
	preset6.push_back(Obstacle(Vector2D(5, 3)));
	preset6.push_back(Obstacle(Vector2D(5, 2)));
	preset6.push_back(Obstacle(Vector2D(3, 2)));
	preset6.push_back(Obstacle(Vector2D(3, 1)));
	preset6.push_back(Obstacle(Vector2D(2, 1)));
	preset6.push_back(Obstacle(Vector2D(6, 0)));
	preset6.push_back(Obstacle(Vector2D(3, 1)));
	preset6.push_back(Obstacle(Vector2D(2, 1)));
	preset6.push_back(Obstacle(Vector2D(6, 0)));
	obstacle_presets.push_back(preset6);
	obstacle_preset_names.push_back("Close Quarters");

	//Special Obstacle Preset
	special_obstacle_preset.push_back(Obstacle(Vector2D(2, 5)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(2, 6)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(3, 6)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(5, 6)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(6, 6)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(6, 5)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(6, 3)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(6, 2)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(5, 2)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(3, 2)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(2, 2)));
	special_obstacle_preset.push_back(Obstacle(Vector2D(2, 3)));
	//
}

void MainMenu::enter_story_mode()
{
	StoryMode story_mode;
	story_mode.story_mode_start();
}

void MainMenu::show_out_message(std::string message)
{
	for (auto c : message)
	{
		std::cout << c;
		Sleep(25);
	}
	std::cout << std::endl;
}



