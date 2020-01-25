#ifndef _WAZA_H_
#define _WAZA_H_
#include <iostream>
#include <array>
#include <utility>
#include <string>


class Waza {
private:
	std::string name = "";
	int type = -1; // dark, normal, etc.
	int power = 0;
	int accuracy = 0;
	int power_points_max = 0;
	int power_points_current = 0;
	int characteristic = -1; // attack (1), special (2), no damage (0)
	int scope = -1; // self (0), one enemy (1), 
	int priority = 0;
	int text_type = -1; // variable to determine what should be displayed in battle
	int additional_effect_percentage = 0;
	std::string description = "";
public:
	Waza();
	Waza(std::string name);
	std::string get_waza_name();
	int get_waza_power();
	int get_waza_accuracy();
	int get_pp_max();
	int get_pp_current();
	int get_priority();
	int get_scope();
	int get_characteristic();
	int get_type();

};


#endif