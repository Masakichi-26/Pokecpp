#ifndef _POKEMON_H_
#define _POKEMON_H_
#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include "Waza.h"


class Pokemon {
private:
//	std::pair<std::string, std::string> info_name; // first element will be nickname, second is pokedex name
	std::string pokedex_name = "";
	std::string nickname = "";
	int pokedex_number = 0;
	std::array<int, 6> info_constants = {0, 0, 0, 0, 0, 0}; // pokedex number, type1, type2, exp curve, gender ratio, defeat exp (level*1/7 * value)
	std::array<int, 3> info_non_constants = {0, 0, 0}; // gender, nature, ability
	std::vector<std::string> egg_group = {""}; // can have more than 1
	std::array<int, 3> level_exp = {1, 0, 0}; // level, total exp, total exp to next level
	std::array<int, 6> stats_main = {1, 0, 0, 0, 0, 0}; // HP, atk, def, sp atk, sp def, spd
	std::array<int, 6> stats_battle = {1, 0, 0, 0, 0, 0};
	std::array<int, 8> stats_battle_stages = { 0, 0, 0, 0, 0, 0, 0, 0 }; // last two are evasion and accuracy, respectively
	std::array<int, 6> stats_base = {0, 0, 0, 0, 0, 0};
	std::array<int, 6> stats_indiv_values = {0, 0, 0, 0, 0, 0};
	std::array<int, 6> stats_effort_values = {0, 0, 0, 0, 0, 0};
	std::vector<Waza> waza_current = {};
public:
	Pokemon();
	Pokemon(std::string pokedex_name, int level);
	Pokemon(int number, int level);
	
	/*
	Pokemon(const Pokemon &source);
	Pokemon(Pokemon &&source);
	~Pokemon();
	*/
	
	std::string get_nickname();
	std::string get_pokedex_name();
	std::array<int, 3> get_level_exp();
	std::array<int, 6> get_stats_indiv_values();
	std::array<int, 6> get_stats_main();
	std::array<int, 6> get_stats_battle();
	std::array<int, 8> get_stats_battles_stages();
	std::array<int, 6> get_stats_base();
	std::array<int, 6> get_info_constants();
	std::array<int, 3> get_info_non_constants();
	std::vector<Waza> get_waza_current();
	int get_waza_current_size();
	void display_status_menu();
	
	void set_stats_main();
	void reset_stats_battle();
	void reset_stats_battle_stages();
	void change_stats_battle_stages(std::array<int, 2> &index_change);
	void update_battle_stats();
	void set_name();
	void set_baseStats_infoConstants();
	std::string display_gender(); // displays gender as a string instead of number
	std::string display_nature(); // displays nature as string instead of number
	void add_exp(const int &exp);
	void deal_damage(const int &damage);
	void display_level_up();

};


#endif