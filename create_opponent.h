#ifndef _CREATE_OPPONENT_H_
#define _CREATE_OPPONENT_H_
#include <string>
#include <map>
#include <array>
#include <vector>
#include "Trainer.h"


std::shared_ptr<Trainer> determine_battle_opponent(const std::string& cur_loc, const int& wild_enc, const int& tnr_enc);
std::vector<std::array<int, 4>> get_wild_pokemon_by_area(const std::string & cur_loc);
Pokemon select_wild_pokemon(const std::vector<std::array<int, 4>> & spawn_list);

#endif