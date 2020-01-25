#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include "create_pokemon.h"


int set_gender(const int &ratio){
	int rn = rand() % 8;
	// 0 means 100% female, 7 means 100% male
	if(ratio == 9)
		return 3; // genderless
	else if(rn < ratio)
		return 1; // male
	else
		return 2; // female
}


int set_nature(){
	int rn = rand() % 25;
	return  rn;
}


std::string display_type(const int& type) {
	if (type == 1)
		return "あく";
	else if (type == 2)
		return "いわ";
	else if (type == 3)
		return "エスパー";
	else if (type == 4)
		return "かくとう";
	else if (type == 5)
		return "くさ";
	else if (type == 6)
		return "ゴースト";
	else if (type == 7)
		return "こおり";
	else if (type == 8)
		return "じめん";
	else if (type == 9)
		return "でんき";
	else if (type == 10)
		return "どく";
	else if (type == 11)
		return "ドラゴン";
	else if (type == 12)
		return "ノーマル";
	else if (type == 13)
		return "はがね";
	else if (type == 14)
		return "ひこう";
	else if (type == 15)
		return "ほのお";
	else if (type == 16)
		return "みず";
	else if (type == 17)
		return "むし";
	else
		return "";
}

std::array<int, 5> get_nature_modifiers(const int &nature){
	std::array<std::array<int, 5>, 25> nature_modifier {{
		{100, 100, 100, 100, 100}, //  0 Hardy
		{110,  90, 100, 100, 100}, //  1 Lonely
		{110, 100, 100, 100,  90}, //  2 Brave
		{110, 100,  90, 100, 100}, //  3 Adamant
		{110, 100, 100,  90, 100}, //  4 Naughty
		{ 90, 110, 100, 100, 100}, // 
		{100, 100, 100, 100, 100},
		{100, 110, 100, 100,  90},
		{100, 110,  90, 100, 100},
		{100, 110, 100,  90, 100},
		{ 90, 100, 100, 100, 110},
		{100,  90, 100, 100, 110},
		{100, 100, 100, 100, 100},
		{100, 100,  90, 100, 110},
		{100, 100, 100,  90, 110},
		{ 90, 100, 110, 100, 100},
		{100,  90, 110, 100, 100},
		{100, 100, 110, 100,  90},
		{100, 100, 100, 100, 100},
		{100, 100, 110,  90, 100},
		{ 90, 100, 100, 110, 100},
		{100,  90, 100, 110, 100},
		{100, 100, 100, 110,  90},
		{100, 100,  90, 110, 100},
		{100, 100, 100, 100, 100}
	}};

	return nature_modifier.at(nature);
}


int set_exp(const int &level, const int &exp_curve){
	std::array<int, 101> exp_table {};
	
	if (exp_curve == 2) {
		exp_table = {0,8,27,64,125,216,343,512,729,1000,1331,1728,2197,2744,3375,4096,4913,5832,6859,8000,9261,10648,12167,13824,15625,17576,19683,21952,24389,27000,29791,32768,35937,39304,42875,46656,50653,54872,59319,64000,68921,74088,79507,85184,91125,97336,103823,110592,117649,125000,132651,140608,148877,157464,166375,175616,185193,195112,205379,216000,226981,238328,250047,262144,274625,287496,300763,314432,328509,343000,357911,373248,389017,405224,421875,438976,456533,474552,493039,512000,531441,551368,571787,592704,614125,636056,658503,681472,704969,729000,753571,778688,804357,830584,857375,884736,912673,941192,970299,1000000};
	}
	else if(exp_curve == 3){
		exp_table = {0,9,57,96,135,179,236,314,419,560,742,973,1261,1612,2035,2535,3120,3798,4575,5460,6458,7577,8825,10208,11735,13411,15244,17242,19411,21760,24294,27021,29949,33084,36435,40007,43808,47846,52127,56660,61450,66505,71833,77440,83335,89523,96012,102810,109923,117360,125126,133229,141677,150476,159635,169159,179056,189334,199999,211060,222522,234393,246681,259392,272535,286115,300140,314618,329555,344960,360838,377197,394045,411388,429235,447591,466464,485862,505791,526260,547274,568841,590969,613664,636935,660787,685228,710266,735907,762160,789030,816525,844653,873420,902835,932903,963632,995030,1027103,1059860};	
	}
	if(level > 0)
		return exp_table.at(level - 1);
	else
		return 0;
}


std::array<int, 6> set_stats_indiv_values(){
//	int constant {0};
	int max_value {32}; // use in modulus
	int rn {};
	std::array<int, 6> ind_val {};
	
	for(size_t i{0}; i < 6; i++){
		rn = rand() % max_value;
		ind_val.at(i) = rn;
	}
	
	return ind_val;
}


std::string init_pokedex_name(const int &num){
	std::map<int, std::string> name_by_number {{
		{  1, "フシギダネ"},
		{  4, "ヒトカゲ"},
		{  7, "ゼニガメ"},
		{ 16, "ポッポ"},
		{ 19, "コラッタ"}
	}};
	
	auto it = name_by_number.find(num);
	if(it != name_by_number.end())
		return it->second;
	else
		return "？？？";
}


std::array<int, 12> get_basic_data(int &number){
	std::array<std::array<int, 12>, 150> basic_data_array{{
		// types
		
		// exp curves
		// 0 = 60・ｽ・ｽ			1 = 80・ｽ・ｽ		2 = 100・ｽ・ｽ		3 = 105・ｽ・ｽ		4 = 125・ｽ・ｽ		5 = 164・ｽ・ｽ

		// base stats x6, number, type1, type2, exp curve, gender ratio, defeat exp (level*1/7 * value)

		{  0,   0,   0,   0,   0,   0,   0,  0,  0, 0, 0,   0},
		{ 45,  49,  49,  65,  65,  45,   1,  5, 10, 3, 7,  64}, 
		{ 45,  49,  49,  65,  65,  45,   2,  5, 10, 3, 7, 141},
		{ 45,  49,  49,  65,  65,  45,   3,  5, 10, 3, 7, 208},
		{ 39,  52,  43,  60,  50,  65,   4, 15,  0, 3, 7,  65},
		{ 39,  52,  43,  60,  50,  65,   5, 15,  0, 3, 7, 142},
		{ 39,  52,  43,  60,  50,  65,   6, 15, 14, 3, 7, 209},
		{ 44,  48,  65,  50,  64,  43,   7, 16,  0, 3, 7,  66},
		{ 44,  48,  65,  50,  64,  43,   8, 16,  0, 3, 7, 143},
		{ 44,  48,  65,  50,  64,  43,   9, 16,  0, 3, 7, 210},
		{  0,   0,   0,   0,   0,   0,  10,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  11,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  12,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  13,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  14,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  15,  0,  0, 0, 0,   0},
		{ 40,  45,  40,  35,  35,  56,  16, 12, 14, 3, 4,  55},
		{  0,   0,   0,   0,   0,   0,  17,  0,  0, 0, 0,   0},
		{  0,   0,   0,   0,   0,   0,  18,  0,  0, 0, 0,   0},
		{ 30,  56,  35,  25,  35,  72,  19, 12,  0, 2, 4,  57}
	}};
	
	return basic_data_array.at(number);
}



int calc_exp_gained(const double &exp_defeat, const int &level, const int &battle_type){
	double type {};
	
	if(battle_type == 2)
		type = 1.5; // trainer battle
	else if(battle_type == 1)
		type = 1.0;
	else
		type = 0.0;
	
	double exp_total = (level/7.0)*exp_defeat * type;
	int exp_gain = std::floor(exp_total);
	
	return exp_gain;
}
