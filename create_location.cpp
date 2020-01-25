#include <map>
#include "create_location.h"


std::array<int, 3> init_location_info(std::string & name) {
	std::map<std::string, std::array<int, 3>> location_list{ {
		{"マサラタウン",		{  0,  0,  0}},
		{"１番道路",			{  3,  3,  0}},
		{"トキワシティ",		{  0,  0,  0}},
	} };

	auto it = location_list.find(name);
	if (it != location_list.end())
		return it->second;
	else
		return { 0, 0, 0 };
}


std::vector<std::string> init_options_info(std::string& name) {
	std::map<std::string, std::vector<std::string>> options_list{ {
		{"マサラタウン",		{{"１番道路に移動する"}}},
		{"１番道路",			{{"前へ進む"},
								{"prへ戻る"}}},
		{"トキワシティ",		{{"１番道路に移動する"}}}
	} };

	auto it = options_list.find(name);
	if (it != options_list.end())
		return it->second;
	else
		return {"何もできない"};
}
