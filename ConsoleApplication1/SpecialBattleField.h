#pragma once
#include "BattleField.h"

class SpecialBattleField : public BattleField
{
private:
	void set_objects_on_positions(MainCharacter &main_character, std::vector <Enemy> &group_of_enemies) override;

public:
	~SpecialBattleField();
};

