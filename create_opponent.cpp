#include <ctime>
#include <cmath>
#include "create_opponent.h"


std::shared_ptr<Trainer> determine_battle_opponent(const std::string& cur_loc, const int& wild_enc, const int& tnr_enc) {
	
//	Pokemon temp_pok;
	std::string enemy_name{};
	std::vector<std::array<int, 4>> spawn_list;

	if (wild_enc > 0) {
		enemy_name = "ñÏê∂";
		std::shared_ptr<Trainer> temp_tnr = std::make_shared<Trainer>(enemy_name);
		spawn_list = get_wild_pokemon_by_area(cur_loc);
		if (!spawn_list.empty()) {
//			Pokemon temp_pok{ select_wild_pokemon(spawn_list) };
			temp_tnr->add_pokemon_to_party(select_wild_pokemon(spawn_list));
		}
		return temp_tnr;
	}
	
}


std::vector<std::array<int, 4>> get_wild_pokemon_by_area(const std::string & cur_loc) {
	std::vector<std::array<int, 4>> list;

	// array elements are as follows
	// [0] maximum rate number (of the pokemon's encounter rate range. minimum is the number after the previous element's number. if none, 0)
	// [1] pokemon's pokedex number
	// [2] lowest level of pokemon
	// [3] highest level of pokemon

	if (cur_loc == "ÇPî‘ìπòH") {
		list = { {
			{ 60,  16,  2,  4}, // 60% chance to encounter
			{100,  19,  2,  4}   // 40% chance to encounter
		} };
	}

	return list;
}


Pokemon select_wild_pokemon(const std::vector<std::array<int, 4>> & spawn_list) {
	int rn = rand() % 100;
	std::array<int, 4> temp{};
	std::cout << "rn: " << rn << std::endl;
	for (auto v: spawn_list) {
		if (rn < v.at(0)) {
			temp = v;
			break;
		}
	}

	int level = rand() % (temp.at(3) - temp.at(2) + 1);
	level += temp.at(2);

	return { temp.at(1), level };
}