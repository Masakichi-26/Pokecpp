#ifndef _BATTLE_ACTION_H_
#define _BATTLE_ACTION_H_
#include <iostream>
#include <vector>
#include "Pokemon.h"
#include "constants.h"


class BattleAction {
private:
	Action::type type;
	std::vector<int> player_targets;
	std::vector<int> enemy_targets;
public:

};

#endif