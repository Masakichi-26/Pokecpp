#ifndef _CREATE_WAZA_H_
#define _CREATE_WAZA_H_

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "Waza.h"

std::array<int, 9> init_waza_info(std::string &waza);
bool check_if_waza_is_stat_changing(Waza &waza);
std::vector<std::array<int, 2>> determine_stat_changes(Waza &waza);

#endif