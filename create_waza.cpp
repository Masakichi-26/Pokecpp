#include <map>
#include "create_waza.h"


std::array<int, 9> init_waza_info(std::string &waza){
	std::map<std::string, std::array<int, 9>> move_list {{
		// Array is in the following order
		// Type, power, accuracy, Max PP, characteristic, scope, speed priority, text type, additional effect percentage
		//										  ch sc	pr tt aep  
		{"えんまく",			{12,  0, 100, 20, 0, 1, 0, 0,  0}},
		{"きあいだめ",			{12,  0,   0, 30, 0, 0, 0, 0,  0}},
		{"こわいかお",			{12,  0,  90, 10, 0, 1, 0, 0,  0}},
		{"しっぽをふる",		{12,  0, 100, 30, 0, 1, 0, 0,  0}},
		{"たいあたり",			{12, 35,  95, 35, 1, 1, 0, 0,  0}},
		{"つるのむち",			{ 5, 35, 100, 15, 1, 1, 0, 0,  0}},
		{"でんこうせっか",		{12, 40, 100, 30, 1, 1, 1, 0,  0}},
		{"どくのこな",			{10,  0,  75, 35, 0, 1, 0, 0,  0}},
		{"なきごえ",			{12,  0, 100, 40, 0, 1, 0, 0,  0}},
		{"ねむりごな",			{ 5,  0,  75, 15, 0, 1, 0, 0,  0}},
		{"ひっかく", 			{12, 40, 100, 35, 1, 1, 0, 0,  0}},
		{"ひのこ",				{15, 40, 100, 25, 2, 1, 0, 0,  0}},
		{"やどりぎのタネ",		{ 5,  0,  90, 10, 0, 1, 0, 0,  0}},
		{"りゅうのいかり",		{11,  0, 100, 10, 2, 1, 0, 0,  0}}

	}};
	
	auto it = move_list.find(waza);
	if(it != move_list.end())
		return it->second;
	else
		return {-1, 0, 0, 0, 0, -1, 0, -1, 0};
}


bool check_if_waza_is_stat_changing(Waza &waza) {
	std::string n = waza.get_waza_name();

	if (n == "なきごえ")
		return true;
	if (n == "こわいかお")
		return true;


	return false;

}

std::vector<std::array<int, 2>> determine_stat_changes(Waza &waza) {
	std::string n = waza.get_waza_name();
	std::vector<std::array<int, 2>> effect{ }; // first one is which stat (0~7), second one is by how many levels (-6~6)

	if (n == "なきごえ")
		effect.emplace_back(std::array <int, 2>{1, -1});
	else if(n == "しっぽをふる")
		effect.emplace_back(std::array <int, 2>{2, -1});
	else if(n == "こわいかお")
		effect.emplace_back(std::array <int, 2>{5, -2});
	else 
		effect.emplace_back(std::array <int, 2>{0, 0});

	return effect;
}