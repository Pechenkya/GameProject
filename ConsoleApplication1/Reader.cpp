#include "Reader.h"
#include "StoryMode.h"
#include "Scene.h"

#include <fstream>
#include <iostream>

std::string Reader::get_language()
{
	std::ifstream input("langconf.txt");
	std::string temp_str;
	std::getline(input, temp_str);
	input.close();

	return temp_str;
}

void Reader::read_file_replics(std::string file_name, Scene &scene_in)
{
	std::string name{};
	std::string temp_string{};
	int temp;
	std::vector <std::string> temp_str_vec_replic;
	std::vector <std::string> temp_str_vec_answ;
	std::vector <std::string> temp_str_vec_answ_result;

	std::ifstream file_input(file_name);

	do
	{
		std::getline(file_input, temp_string);

		if (temp_string == "/0")
		{
			std::getline(file_input, name);
		}
		else if (temp_string == "/1")
		{
			name = "Teller";
		}

		std::getline(file_input, temp_string);
		temp = std::stoi(temp_string);

		for (int i{ 0 }; i < temp; i++)
		{
			std::getline(file_input, temp_string);
			temp_str_vec_replic.push_back(temp_string); //Getting replic line
		}

		std::getline(file_input, temp_string);
		temp = std::stoi(temp_string);

		for (int i{ 0 }; i < temp; i++)
		{
			std::getline(file_input, temp_string);
			temp_str_vec_answ.push_back(temp_string); //Getting answer

			std::getline(file_input, temp_string);
			temp_str_vec_answ_result .push_back(temp_string); //Getting amswer results
		}

		scene_in.add_replic(temp_str_vec_replic, name, temp_str_vec_answ, temp_str_vec_answ_result);
		temp_str_vec_replic.clear();
		temp_str_vec_answ.clear();
		
		

		std::getline(file_input, temp_string);

		if (temp_string == "/end") break;

		std::getline(file_input, temp_string);

	} while (temp_string != "/end");
	
	file_input.close();
}

void Reader::read_file_mc_saves(StoryMode *new_st_mode)
{
	int temp_num{};
	std::string temp_str{};

	std::ifstream file_input("maincharsave.txt");

	file_input >> new_st_mode->current_chapter;
	std::getline(file_input, temp_str);

	std::getline(file_input, temp_str);
	StoryMode::main_character->name = temp_str;

	file_input >> temp_num;
	StoryMode::main_character->set_health(temp_num);
	std::getline(file_input, temp_str);

	std::getline(file_input, temp_str);
	for (auto &w : BattleMode::weapon_list)
	{
		if (w.get_model() == temp_str.substr(0, w.get_model().size()))
		{
			StoryMode::main_character->set_weapon(&w);
			break;
		}
	}

	std::getline(file_input, temp_str);
	for (auto &w : BattleMode::weapon_list)
	{
		if (w.get_model() == temp_str.substr(0, w.get_model().size()))
		{
			StoryMode::main_character->set_weapon(&w);
			break;
		}
	}

	file_input >> temp_num;
	StoryMode::main_character->set_agility(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->set_strength(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->set_accuracy(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->set_stealth(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->set_lvl_points(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->add_syringes(temp_num);
	std::getline(file_input, temp_str);

	file_input >> temp_num;
	StoryMode::main_character->set_karma(temp_num);
	std::getline(file_input, temp_str);

	file_input.close();
}

void Reader::save_file_mc_saves(StoryMode *new_st_mode)
{
	std::ofstream save_file("maincharsave.txt");

	save_file.trunc;

	save_file << new_st_mode->current_chapter << " /Chapter" << std::endl;
	save_file << StoryMode::main_character->name << std::endl;
	save_file << StoryMode::main_character->get_health_int() << " /Health" << std::endl;
	save_file << StoryMode::main_character->get_weapon()->get_model() << " /Weapon(primary)" << std::endl;
	StoryMode::main_character->swap_weapon();
	save_file << StoryMode::main_character->get_weapon()->get_model() << " /Weapon(secondary)" << std::endl;
	save_file << StoryMode::main_character->get_agility() << " /Agility" << std::endl;
	save_file << StoryMode::main_character->get_strength() << " /Strength" << std::endl;
	save_file << StoryMode::main_character->get_additiona_accuracy() << " /Aditional accuracy" << std::endl;
	save_file << StoryMode::main_character->get_stealth() << " /Stealth" << std::endl;
	save_file << StoryMode::main_character->get_lvl_points() << " /Leveling points" << std::endl;
	save_file << StoryMode::main_character->get_syringes_count() << " /Syringes" << std::endl;
	save_file << StoryMode::main_character->get_karma() << " /Karma" << std::endl;

	save_file.close();
}

void Reader::reset_mc_saves()
{
	std::string temp_str;
	std::ofstream save_file("maincharsave.txt");
	std::ifstream const_file("maincharconstsave.txt");
	save_file.trunc;

	do
	{

		std::getline(const_file, temp_str);
		save_file << temp_str << std::endl;

	} while (temp_str != "/end");

	save_file.close();
	const_file.close();
}


void Reader::reset_char_save(std::string backup_file, std::string read_file)
{
	std::string temp_str;
	std::ofstream char_file(read_file);
	std::ifstream backup(backup_file);
	char_file.trunc;

	do
	{

		std::getline(backup, temp_str);
		char_file << temp_str << std::endl;

	} while (temp_str != "/end");

	char_file.close();
	backup.close();
}


void Reader::recover_chapter(std::string backup_file, std::string chapeter_file)
{
	std::string temp_str;
	std::ofstream chap_file(chapeter_file);
	std::ifstream backup(backup_file);
	chap_file.trunc;

	do
	{

		std::getline(backup, temp_str);
		chap_file << temp_str << std::endl;

	} while (temp_str != "/end");

	chap_file.close();
	backup.close();
}


void Reader::read_file_char_saves(Character & character, std::string file_name)
{
	int temp_num{};
	std::string temp_str{};

	std::ifstream file_input(file_name);

	std::getline(file_input, character.name);

	std::getline(file_input, temp_str);
	if (temp_str.substr(0, 4) == "true")
		character.set_life_status(true);
	else
		character.set_life_status(false);

	std::getline(file_input, temp_str);
	character.set_health(std::stoi(temp_str.substr(0, 4)));

	std::getline(file_input, temp_str);
	character.set_max_health(std::stoi(temp_str.substr(0, 4)));

	std::getline(file_input, temp_str);
	for (auto &w : BattleMode::weapon_list)
	{
		if (w.get_model() == temp_str.substr(0, w.get_model().size()))
		{
			character.set_weapon(&w);
			break;
		}
	}

	std::getline(file_input, temp_str);
	character.set_loyalty(std::stoi(temp_str.substr(0, 4)));

	std::getline(file_input, temp_str);
	character.set_agility(std::stoi(temp_str.substr(0, 4)));

	file_input.close();
}

void Reader::save_file_char_saves(Character & character, std::string file_name)
{
	std::ofstream file_output(file_name);

	file_output.trunc;

	file_output << character.name << std::endl;

	if (character.get_alive_status())
		file_output << "true";
	else
		file_output << "false";
	file_output << " //Alive Status" << std::endl;

	file_output << character.get_health_int() << " //Health" << std::endl;

	file_output << character.get_max_health() << " //Max Health" << std::endl;

	file_output << character.get_weapon()->get_model() << " //Using Weapon" << std::endl;

	file_output << character.get_loyalty() << " //Loyalty level" << std::endl;

	file_output << character.get_agility() << " //Agility" << std::endl;

	file_output.close();
}

Reader::Reader()
{
}


Reader::~Reader()
{
}
