#include "SpecialBattleField.h"



void SpecialBattleField::set_objects_on_positions(MainCharacter & main_character, std::vector<Enemy>& group_of_enemies)
{
	main_character.set_on_pos((battle_field_size / 2), (battle_field_size / 2));

	int h1{};
	int h2{};
	int h3{};
	int h4{};
	for (int i = 0; i < group_of_enemies.size(); i++)
	{
		if ((i + 1) % 4 == 0) 
		{
			if(h1%2 != 0)
				group_of_enemies.at(i).set_on_pos(8, 0 + (h1 + 1) / 2);
			else
				group_of_enemies.at(i).set_on_pos(8 - h1 / 2, 0);
			h1++;
		} 
		else if ((i + 1) % 3 == 0)
		{
			if (h2 % 2 != 0)
				group_of_enemies.at(i).set_on_pos(0, 0 + (h1 + 1) / 2);
			else
				group_of_enemies.at(i).set_on_pos(0 + h1 / 2, 0);
			h2++;
		}
		else if ((i + 1) % 2 == 0 && (i + 1) % 4 != 0)
		{
			if (h3 % 2 != 0)
				group_of_enemies.at(i).set_on_pos(8, 8 - (h3 + 1) / 2);
			else
				group_of_enemies.at(i).set_on_pos(8 - h3 / 2, 8);
			h3++;
		}
		else
		{
			if (h4 % 2 != 0)
				group_of_enemies.at(i).set_on_pos(0, 8 - (h4 + 1) / 2);
			else
				group_of_enemies.at(i).set_on_pos(0 + h4 / 2, 8);
			h4++;
		}
	}
}

SpecialBattleField::~SpecialBattleField()
{
}
