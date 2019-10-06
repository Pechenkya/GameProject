#include "Scene.h"
#include "windows.h"
#include "StoryMode.h"
#include "Character.h"

void Scene::add_replic(std::vector<std::string> new_replic, std::string author, std::vector <std::string> answer_list, std::vector <std::string> answer_results)
{
	replic_pool.push_back(Replic(new_replic, author, answer_list, answer_results));
}

void Scene::play_replic(int replic_num)
{
	replic_num--;

	system("CLS");

	if (replic_pool.at(replic_num).name_of_author != "Teller")
		std::cout << replic_pool.at(replic_num).name_of_author << ":" << std::endl;

	for (auto r : (replic_pool.at(replic_num).replic))
	{
		for (auto c : r)
		{
			std::cout << c;
			if (c == '.' || c == '!') 
				Sleep(140);
			Sleep(70);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	Sleep(400);

	int i{ 1 };
	for (auto a : (replic_pool.at(replic_num).answer))
	{
		std::cout << i << " - " << a << std::endl;
		i++;
	}

	if (replic_pool.at(replic_num).answer.size() == 0) system("Pause");
	else std::cout << std::endl;

}

void Scene::redeem_key(int replic_num, int special_key)
{
	replic_num--;
	special_key--;

	std::string result{ this->replic_pool.at(replic_num).answer_results.at(special_key) };
	std::string character_name;

	if (result.substr(0, 5) == "Karma")
	{
		StoryMode::main_character->increase_karma(stoi(result.substr(6, result.size() - 6)));
	}
	else if (result.substr(0, 4) == "Kill")
	{
		for (auto c : StoryMode::character_list)
		{
			character_name = c->name;
			if (c->name == result.substr(5, character_name.size()))
				c->get_killed();
		}
	}
	else
	{
		for (auto c : StoryMode::character_list)
		{
			character_name = c->name;
			if (c->name == result.substr(0, character_name.size()))
				c->increase_loyalty(stoi(result.substr(character_name.size() + 1, result.size() - (character_name.size() + 1))));
		}
	}
}


Scene::Scene(std::string sc_name)
{
	scene_name = sc_name;
}

Scene::Scene() : Scene("Scene") {};

Scene::~Scene()
{
}

Replic::Replic(std::vector<std::string> new_replic, std::string author_in, std::vector <std::string> answer_list, std::vector <std::string> answer_results_in)
{
	replic = new_replic;
	name_of_author = author_in;
	if(name_of_author != "Teller")
		for (auto t : StoryMode::character_list)
		{
			if (t->name == name_of_author)
				author = t;
		}
	answer_results = answer_results_in;
	answer = answer_list;
}
