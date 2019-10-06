#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "windows.h"
#include <list>
#include <queue>

//random
int random_gen()
{
	return (rand()) % 1000;
};

//Objects
#include "Object.h"
#include "Character.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Obstacle.h"

//Weapon
#include "Weapon.h"
#include "Firearms.h"
#include "MeleeWeapon.h"

//Assising classes
#include "Vector2D.h"
#include "Pathfinding.h"
#include "MainMenu.h"
#include "Reader.h"

//Locations
#include "BattleField.h"
#include "StoryMode.h"
#include "BattleMode.h"

int main()
{
	srand(time(NULL));
	//Setting console
	system("mode con cols=130 lines=40");

	MainMenu game_starts;
	game_starts.user_menu();
	return 0;

}


//Shooting testing
/*
	Vector2D new_vec_a(4, 4);
	Vector2D new_vec_b(1, 2);
	Vector2D new_vec_c1(2, 2);
	Vector2D new_vec_c2(2, 3);

	NormalizedVec vec_AB = new_vec_a.get_normalized_vec(new_vec_b);
	NormalizedVec vec_AC1 = new_vec_a.get_normalized_vec(new_vec_c1);
	NormalizedVec vec_AC2 = new_vec_a.get_normalized_vec(new_vec_c2);

	if (vec_AB == vec_AC1)
		std::cout << "You can't shoot through C1 + ";
	else
		std::cout << "You can shoot through C1 - ";

	std::cout << "\n";

	if (vec_AB == vec_AC2)
		std::cout << "You can't shoot through C2 + ";
	else
		std::cout << "You can shoot through C2 - ";

	std::cout << "\n";

	std::cout << vec_AB.pos_x << " " << vec_AB.pos_y;
	std::cout << "\n";

	std::cout << vec_AC1.pos_x << " " << vec_AC1.pos_y;
	std::cout << "\n";

	std::cout << vec_AC2.pos_x << " " << vec_AC2.pos_y;
	std::cout << "\n";
	*/