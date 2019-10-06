#include "StoryMode.h"
#include "Reader.h"
#include "BattleField.h"
#include "Enemy.h"
#include "MainMenu.h"

std::list <Character*> StoryMode::character_list;

MainCharacter* StoryMode::main_character;

void StoryMode::reset_saves()
{

	Reader::reset_mc_saves();

	//Characters reset

	Reader::reset_char_save("matthewcharconstsave.txt", "matthewcharsave.txt");

	//Scene reset

	StoryMode::recover_chapters();
	
}

void StoryMode::recover_chapters()
{

	if (Reader::get_language() == "English")
	{
		Reader::recover_chapter("practicechapen.txt", "practicechap.txt");
	}

}

void StoryMode::chapter_practice()
{
	do
	{
		int input{};
		int replic_counter{ 1 };
		Practice.play_replic(replic_counter);
		std::cin >> input;

		Practice.redeem_key(replic_counter, input);
		replic_counter++;

		Practice.play_replic(replic_counter);
		std::cin >> input;
		Practice.redeem_key(replic_counter, input);
		replic_counter += input;

		Practice.play_replic(replic_counter);
		replic_counter += (5 - input);

		Practice.play_replic(replic_counter);
		replic_counter++;

		Practice.play_replic(replic_counter);
		replic_counter++;

		Practice.play_replic(replic_counter);
		replic_counter++;

		main_character->increase_skills();

		Practice.play_replic(replic_counter);
		std::cin >> input;
		Practice.redeem_key(replic_counter, input);

		switch (input)
		{
		case 1:
		{
			main_character->set_weapon(&BattleMode::weapon_list.at(2)); //Deagle
			break;
		}
		case 2:
		{
			main_character->set_weapon(&BattleMode::weapon_list.at(1)); //AK-74
			break;
		}
		case 3:
		{
			main_character->set_weapon(&BattleMode::weapon_list.at(0)); //Nova
			break;
		}
		case 4:
		{
			main_character->set_weapon(&BattleMode::weapon_list.at(3)); //Kukri
			break;
		}
		default:
			break;
		}

		replic_counter += input;
		Practice.play_replic(replic_counter);


		replic_counter += (5 - input);
		Practice.play_replic(replic_counter);
		std::cin >> input;

		main_character->add_syringes(5);

		if (input == 1 && main_character->get_stealth() >= 1)
			replic_counter += 2;
		else 
		{
			bool temp_surr_st{ false };
			BattleField new_bf;
			std::vector <Enemy> group_of_enemies;
			group_of_enemies.push_back(Enemy("Robot 1", 130, &BattleMode::weapon_list.at(5)));
			group_of_enemies.push_back(Enemy("Robot 2", 130, &BattleMode::weapon_list.at(5)));
			group_of_enemies.push_back(Enemy("Robot 3", 130, &BattleMode::weapon_list.at(3)));
			group_of_enemies.push_back(Enemy("Robot 4", 130, &BattleMode::weapon_list.at(3)));

			system("mode con cols=200 lines=51");
			new_bf.new_battle(*main_character, group_of_enemies, MainMenu::obstacle_presets.at(5), temp_surr_st);
			system("mode con cols=130 lines=40");

			if ((temp_surr_st || !main_character->get_alive_status()) && input == 2)
			{
				replic_counter++;
				main_character->set_life_status(false);
			} 
			else if ((temp_surr_st || !main_character->get_alive_status()) && input == 1)
			{
				replic_counter += 2;
				main_character->set_life_status(false);
			}

		}

		if (!main_character->get_alive_status())
		{
			Practice.play_replic(replic_counter);
			break;
		}

		replic_counter += input;
		Practice.play_replic(replic_counter);
		if (input == 1) replic_counter++;

		std::cin >> input;
		Practice.redeem_key(replic_counter, input);
		if(input == 2) replic_counter++;

		Practice.play_replic(replic_counter);
		if (input == 2) replic_counter++;

		Practice.play_replic(replic_counter);

		main_character->reset_health();

	} while (false);
}


void StoryMode::story_mode_start()
{
	switch (current_chapter)
	{
	case 0:
	{
		this->chapter_practice();
		if (!main_character->get_alive_status()) break;
		current_chapter++;
		Reader::save_file_mc_saves(this);
	}

	default:
		break;
	}
}

StoryMode::StoryMode()
{

	main_character = new MainCharacter;
	Reader::read_file_mc_saves(this);

	Practice = Scene("Practice");
	StoryMode::recover_chapters();
	Reader::read_file_replics("practicechap.txt", Practice);

	Matthew = Character();
	Reader::read_file_char_saves(Matthew, "matthewcharsave.txt");
	character_list.push_back(&Matthew);

}


StoryMode::~StoryMode()
{
	delete main_character;
}
