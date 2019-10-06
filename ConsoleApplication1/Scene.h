#pragma once
#include <vector>
#include <string>
#include <iostream>

class StoryMode;
class Character;

struct Replic
{
	std::vector <std::string> replic;
	std::vector <std::string> answer_results;
	std::string name_of_author;
	Character* author{ nullptr };

	std::vector <std::string> answer;

	Replic(std::vector <std::string> new_replic, std::string author_in, std::vector <std::string> answer_list, std::vector <std::string> answer_results_in);
};


class Scene
{
private:
	std::string scene_name;
	std::vector <Replic> replic_pool;
public:

	void add_replic(std::vector <std::string> new_replic, std::string author, std::vector <std::string> answer_list, std::vector <std::string> answer_results);
	
	void play_replic(int replic_num);
	void redeem_key(int replic_num, int special_key);

	Scene(std::string sc_name);
	Scene();
	~Scene();
};

