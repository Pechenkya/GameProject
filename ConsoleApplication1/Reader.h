#pragma once
#include <fstream>

class Scene;
class StoryMode;
class Character;

class Reader
{
public:
	static std::string get_language();

	static void read_file_replics(std::string file_name, Scene &scene_in);

	static void read_file_mc_saves(StoryMode *new_st_mode);
	static void save_file_mc_saves(StoryMode *new_st_mode);
	static void reset_mc_saves();
	
	static void read_file_char_saves(Character &character, std::string file_name);
	static void save_file_char_saves(Character &character, std::string file_name);
	static void reset_char_save(std::string backup_file, std::string read_file);

	static void recover_chapter(std::string backup_file, std::string chapeter_file);

	Reader();
	~Reader();
};

