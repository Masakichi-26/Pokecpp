#ifndef _WAZA_LIST_LEVELUP_H_
#define _WAZA_LIST_LEVELUP_H_
#include <iostream>
#include <array>
#include <utility>
#include <string>
#include <map>
#include <vector>
#include "Waza.h"

void check_waza(const int &num, const int &lev, const int &status, std::vector<Waza> &current_moveset);
std::vector<Waza> init_waza(std::multimap<int, std::string> &moveset, const int &lev);
void learn_new_waza(std::multimap<int, std::string> &moveset, std::string &new_move, const int &lev, std::vector<Waza> &current_moveset);

#endif