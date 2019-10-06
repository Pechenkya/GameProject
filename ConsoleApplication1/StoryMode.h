#pragma once
#include "BattleMode.h"
#include "Character.h"
#include "MainCharacter.h"
#include <list>
#include <string>

#include "Scene.h"

class StoryMode
{
private:
	//Scenes
	Scene Practice;

	//Practice
	Character Matthew;
public:
	//Characters
	static std::list <Character*> character_list;
	static MainCharacter* main_character;

	//Special options
	unsigned int current_chapter{ 0 };

	static void reset_saves();

	static void recover_chapters();

	void chapter_practice();
	void story_mode_start();

	StoryMode();
	~StoryMode();
};

