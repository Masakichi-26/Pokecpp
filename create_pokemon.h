#ifndef _CREATE_POKEMON_H_
#define _CREATE_POKEMON_H_

#include <iostream>
#include <array>
#include <string>
#include "Pokemon.h"


//std::array<int, 6> Pokemon::set_stats_base(const std::string &name);
//std::array<int, 6> set_stats_main(const std::array<int, 6> &base, const std::array<int, 6> &indiv, const std::array<int, 6> &effort, const int &lev, const std::string &nature);
std::array<int, 5> get_nature_modifiers(const int &nature);
int set_exp(const int &level, const int &exp_curve);
std::array<int, 6> set_stats_indiv_values();
int set_gender(const int &ratio);
std::string display_type(const int& nature);
int set_nature();
std::array<int, 12> get_basic_data(int &number);
int calc_exp_gained(const double &exp_defeat, const int &level, const int &battle_type);
std::string init_pokedex_name(const int &num);

#endif